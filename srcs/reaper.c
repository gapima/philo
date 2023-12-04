#include "philo.h"

static void	set_sim_stop_flag(t_table *table, bool state)
{
	pthread_mutex_lock(&table->sim_stop_lock);
	table->sim_stop = state;
	pthread_mutex_unlock(&table->sim_stop_lock);
}

bool	has_simulation_stopped(t_table *table)
{
	bool	r;

	r = false;
	pthread_mutex_lock(&table->sim_stop_lock);
	if (table->sim_stop == true)
		r = true;
	pthread_mutex_unlock(&table->sim_stop_lock);
	return (r);
}

static bool	kill_philo(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal) >= philo->table->time_to_die)
	{
		set_sim_stop_flag(philo->table, true);
		write_status(philo, true, DIED);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (true);
	}
	return (false);
}

static bool	end_condition_reached(t_table *table)
{
	unsigned int	i;
	bool			all_ate_enough;

	all_ate_enough = true;
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philos[i]->meal_time_lock);
		if (kill_philo(table->philos[i]))
			return (true);
		if (table->must_eat_count != -1)
			if (table->philos[i]->times_ate
				< (unsigned int)table->must_eat_count)
				all_ate_enough = false;
		pthread_mutex_unlock(&table->philos[i]->meal_time_lock);
		i++;
	}
	if (table->must_eat_count != -1 && all_ate_enough == true)
	{
		set_sim_stop_flag(table, true);
		return (true);
	}
	return (false);
}

void	*reaper(void *data)
{
	t_table			*table;

	table = (t_table *)data;
	if (table->must_eat_count == 0)
		return (NULL);
	set_sim_stop_flag(table, false);
	start_delay(table->start_time);
	while (true)
	{
		if (end_condition_reached(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
