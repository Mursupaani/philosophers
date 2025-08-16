/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:07:04 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/14 18:25:28 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

bool	take_forks(t_philo *philo)
{
	t_philo	*philo_1;
	t_philo	*philo_2;

	if (philo->index % 2 == 0)
	{
		philo_1 = philo;
		philo_2 = &philo->table->philos[philo->index_next];
	}
	else
	{
		philo_1 = &philo->table->philos[philo->index_next];
		philo_2 = philo;
	}
	if (!lock_fork(philo, philo_1))
		return (false);
	if (!lock_fork(philo, philo_2))
	{
		free_fork(philo_1);
		return (false);
	}
	return (true);
}

void	return_forks(t_philo *philo)
{
	t_philo	*philo_1;
	t_philo	*philo_2;

	if (philo->index % 2 == 0)
	{
		philo_1 = philo;
		philo_2 = &philo->table->philos[philo->index_next];
	}
	else
	{
		philo_1 = &philo->table->philos[philo->index_next];
		philo_2 = philo;
	}
	free_fork(philo_1);
	free_fork(philo_2);
}

bool	lock_fork(t_philo *philo, t_philo *philo_to_lock)
{
	if (philo->table->num_of_philos_created == 1)
	{
		while (!philo_to_lock->fork_free && is_philo_alive(philo))
			usleep(PHILO_SLEEP_CYCLE_LENGTH);
		if (!is_philo_alive(philo))
			return (false);
		pthread_mutex_lock(&philo_to_lock->fork_mutex);
		philo_to_lock->fork_free = false;
	}
	else
		pthread_mutex_lock(&philo_to_lock->fork_mutex);
	if (!print_philo_state(philo, TAKE_FORK))
	{
		pthread_mutex_unlock(&philo_to_lock->fork_mutex);
		return (false);
	}
	return (true);
}

void	free_fork(t_philo *philo_to_free)
{
	pthread_mutex_unlock(&philo_to_free->fork_mutex);
	if (philo_to_free->table->num_of_philos_created == 1)
		philo_to_free->fork_free = true;
}
