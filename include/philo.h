#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo	t_philo;

typedef struct s_table
{
	time_t			start_time;
	unsigned int	nb_philos;
	pthread_t		reaper;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_count;
	bool			sim_stop;
	pthread_mutex_t	sim_stop_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
	t_philo			**philos;
}	t_table;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	id;
	unsigned int	times_ate;
	unsigned int	fork[2];
	pthread_mutex_t	meal_time_lock;
	time_t			last_meal;
	t_table			*table;
}	t_philo;

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK_1 = 4,
	GOT_FORK_2 = 5
}	t_status;

//	parsing.c
bool	is_valid_input(int ac, char **av);
int		integer_atoi(char *str);

//	init.c
t_table	*init_table(int ac, char **av, int i);

//	routines.c
void	*routine(void *data);

//	time.c
time_t	get_time_in_ms(void);
void	philo_sleep(t_table *table, time_t sleep_time);
void	start_delay(time_t start_time);

//	output.c
void	write_status(t_philo *philo, bool reaper, t_status status);
void	*error_null(char *str, char *details, t_table *table);
int		msg(char *str, char *detail, int exit_no);

//	reaper.c
void	*reaper(void *data);
bool	has_simulation_stopped(t_table *table);

//	exit.c
int		error_failure(char *str, char *details, t_table *table);
void	*free_table(t_table *table);
void	destroy_mutexes(t_table *table);

#endif