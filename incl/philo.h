/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:45:07 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/14 18:49:19 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <stdatomic.h>

# define PHILO_WAIT_TIME 500
# define PHILO_SLEEP_CYCLE_LENGTH 1000
# define MAX_PHILOS 500

typedef struct s_philosoper	t_philosopher;

typedef struct s_table
{
	t_philosopher	*philos;
	int				params[5];
	atomic_int		num_of_philos_created;
	atomic_int		num_of_forks_mutexes_created;
	atomic_int		num_of_threads_created;
	atomic_int		simulation_over;
	atomic_int		all_philosophers_ready;
	pthread_mutex_t	print_mutex;
	bool			print_mutex_init;
	pthread_mutex_t	time_mutex;
	bool			time_mutex_init;
	struct timeval	start_time;
}	t_table;

typedef struct s_philosoper
{
	pthread_t		philo;
	atomic_int		alive;
	pthread_mutex_t	fork_mutex;
	atomic_int		fork_free;
	atomic_int		finished_eating;
	int				index;
	int				n;
	int				index_next;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_to_eat;
	size_t			last_meal_time;
	struct timeval	start_time;
	struct timeval	time_now;
	t_table			*table;
}	t_philo;

enum	e_input_args
{
	PHILO_COUNT,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	TIMES_TO_EAT
}	;

enum	e_philo_state
{
	THINKING,
	TAKE_FORK,
	EATING,
	SLEEPING,
}	;

enum	e_error
{
	ERR_ARG_COUNT,
	ERR_INIT_TABLE,
	ERR_PARSING,
	ERR_EAT_TIMES,
	ERR_PHILO_COUNT,
	ERR_INIT_PHILO,
	ERR_INIT_MUTEXES,
	ERR_INIT_FINISH_EAT,
	ERR_PHILO_THREADS,
	ERR_OBSERVER_THREAD
}	;

bool	parse_input_args(int ac, char **av, t_table *table);
bool	print_philo_state(t_philo *philo, int state);
int		*ft_atoi_safe(const char *nptr);
void	*routine_even(void *arg);
void	*routine_odd(void *arg);
bool	routine_observer(t_table *table);
bool	free_app_memory(t_table *table);
int		elapsed_time(t_philo *philo);
t_table	*init_table(void);
bool	init_table_mutexes(t_table *table);
bool	init_philosophers(t_table *table);
bool	init_philo_mutexes(t_table *table);
int		ms_between_meals(t_philo *philo);
void	make_even_philos_wait(t_philo *philo);
bool	wait_for_philosophers_to_be_ready(t_philo *philo);
bool	is_philo_alive(t_philo *philo);
void	update_eat_times_and_flag(t_philo *philo);
void	check_death_during_sleeping(t_philo *philo);
bool	take_forks(t_philo *philo);
bool	lock_fork(t_philo *philo, t_philo *philo_to_lock);
void	return_forks(t_philo *philo);
void	free_fork(t_philo *philo_to_free);
void	ft_putstr_fd(char *s, int fd);
int		print_error_and_free_memory(t_table *table, int error);
int		ft_itoa_to_buf(int n, char *dest, size_t buf_size);
bool	philo_think(t_philo *philo);
bool	philo_sleep(t_philo *philo);
bool	philo_eat(t_philo *philo);
void	store_start_time(t_philo *philo);
void	make_odd_routine_philos_wait(t_philo *philo);
void	*routine_single_philo(t_philo *philo);

#endif
