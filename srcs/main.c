#include "philo.h"

static bool	start_simulation(t_table *table)
{
	unsigned int	i;

	table->start_time = get_time_in_ms() + (table->nb_philos * 2 * 10);
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL,
				&routine, table->philos[i]) != 0)
			return (error_failure("%s error: Thread error.\n",
					NULL, table));
		i++;
	}
	if (table->nb_philos > 1)
	{
		if (pthread_create(&table->reaper, NULL,
				&reaper, table) != 0)
			return (error_failure("%s error: Thread error.\n",
					NULL, table));
	}
	return (true);
}

static void	stop_simulation(t_table	*table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	if (table->nb_philos > 1)
		pthread_join(table->reaper, NULL);
	destroy_mutexes(table);
	free_table(table);
}

int	main(int ac, char **av)
{
	t_table	*table;

	table = NULL;
	if (ac - 1 < 4 || ac - 1 > 5)
		return (msg("%s usage: ./philo <number_of_philosophers>" \
		" <time_to_die> <time_to_eat> <time_to_sleep>" \
		" [number_of_times_each_philosopher_must_eat]\n", NULL, EXIT_FAILURE));
	if (!is_valid_input(ac, av))
		return (EXIT_FAILURE);
	table = init_table(ac, av, 1);
	if (!table)
		return (EXIT_FAILURE);
	if (!start_simulation(table))
		return (EXIT_FAILURE);
	stop_simulation(table);
	return (EXIT_SUCCESS);
}
