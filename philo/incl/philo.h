/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:45:07 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/06 12:28:06 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>

typedef struct s_app
{
	int				params[5];
	pthread_t		*philos;
	pthread_mutex_t	*forks_mutexes;
	bool			all_philosophers_alive;
}	t_app;

enum	e_
{
	PHILOS_COUNT,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	TIMES_TO_EAT
}	;

void	parse_input_args(int ac, char **av, t_app *app);
int		*ft_atoi_safe(const char *nptr);
void	exit_failure(t_app *app);
void	*philo_routine(void *arg);
void	join_philosophers_to_main(t_app *app);
void	destroy_forks_mutexes(t_app *app);
void	free_app_memory(t_app *app);

#endif
