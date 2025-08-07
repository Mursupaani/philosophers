/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:45:07 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/06 17:05:46 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <signal.h>

typedef struct s_philosoper t_philosopher;

typedef struct s_table
{
	int				params[5];
	int				num_of_philos_created;
	int				num_of_mutexes_created;
	sig_atomic_t	all_philosophers_alive;
	sig_atomic_t	all_philosophers_ready;
	pthread_mutex_t	alive_mutex;
	t_philosopher	*philos;
	size_t			start_time;
}	t_table;

typedef struct s_philosoper
{
	pthread_t		philo;
	pthread_mutex_t	fork_mutex;
	int				index;
	int				index_next;
	size_t			time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				times_to_eat;
	size_t			last_meal_time;
	t_table			*table;
}	t_philo;

enum	e_input_args
{
	COUNT,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	TIMES_TO_EAT
}	;

bool	parse_input_args(int ac, char **av, t_table *table);
int		*ft_atoi_safe(const char *nptr);
void	*routine(void *arg);
void	join_philosophers_to_main(t_table *table);
void	destroy_forks_mutexes(t_table *table);
void	free_app_memory(t_table *table);
size_t	time_now(struct timeval *time, t_philo *philo);

#endif
