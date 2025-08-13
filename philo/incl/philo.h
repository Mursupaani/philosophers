/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:45:07 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/11 14:31:50 by anpollan         ###   ########.fr       */
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

# define ODD_PHILO_WAIT_TIME 500
# define PHILO_SLEEP_CYCLE_LENGTH 1000
# define MAX_PHILOS 500

typedef struct s_philosoper	t_philosopher;

typedef struct s_table
{
	int				params[5];
	int				num_of_philos_created;
	int				num_of_forks_mutexes_created;
	int				num_of_forks_free_mutexes_created;
	int				num_of_threads_created;
	pthread_mutex_t	all_alive_mutex;
	bool			all_alive_mutex_init;
	bool			all_philosophers_alive;
	pthread_mutex_t	all_ready_mutex;
	bool			all_ready_mutex_init;
	bool			all_philosophers_ready;
	pthread_mutex_t	time_mutex;
	bool			time_mutex_init;
	pthread_mutex_t	finished_eating_mutex;
	bool			finised_eating_mutex_init;
	bool			*finished_eating;
	pthread_mutex_t	philo_dead_mutex;
	bool			philo_dead_mutex_init;
	bool			*philo_dead;
	bool			all_finished_eating;
	t_philosopher	*philos;
	struct timeval	start_time;
}	t_table;

typedef struct s_philosoper
{
	pthread_t		philo;
	bool			alive;
	pthread_mutex_t	fork_mutex;
	bool			fork_free;
	pthread_mutex_t	fork_free_mutex;
	int				index;
	int				n;
	int				index_next;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				times_to_eat;
	size_t			last_meal_time;
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
	DEAD
}	;

enum	e_error
{
	ERR_ARG_COUNT,
	ERR_INIT_TABLE,
	ERR_PARSING,
	ERR_INIT_PHILO,
	ERR_INIT_MUTEXES,
	ERR_INIT_FINISH_EAT,
	ERR_PHILO_THREADS,
	ERR_OBSERVER_THREAD
}	;

bool	parse_input_args(int ac, char **av, t_table *table);
int		*ft_atoi_safe(const char *nptr);
void	*routine(void *arg);
bool	observer_routine(t_table *table);
bool	free_app_memory(t_table *table);
size_t	elapsed_time(t_philo *philo);
bool	init_table_mutexes(t_table *table);
t_table	*init_table(void);
bool	init_philosophers(t_table *table);
bool	init_philo_mutexes(t_table *table);
size_t	ms_between_meals(t_philo *philo);
void	make_odd_philos_wait(t_philo *philo);
void	wait_for_philosophers_to_be_ready(t_philo *philo);
bool	all_philos_alive(t_philo *philo);
void	print_philo_state(t_philo *philo, int state);
bool	is_philo_alive(t_philo *philo);
void	return_forks(t_philo *philo);
// bool	init_finished_eating_flags(t_table *table);
bool	init_end_condition_flags(t_table *table);
void	update_eat_times_and_flag(t_philo *philo);
void	check_death_during_sleeping(t_philo *philo);
bool	lock_fork(t_philo *philo, t_philo *philo_to_lock);
void	free_fork(t_philo *philo_to_free);
bool	take_forks(t_philo *philo);
bool	all_philosophers_ate_enough(t_philo *philo);
void	ft_putstr_fd(char *s, int fd);
int		print_error_and_free_memory(t_table *table, int error);

#endif
