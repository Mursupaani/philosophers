/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:07:04 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/11 14:55:58 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

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
	if (!lock_fork(philo, philo_1) || !is_philo_alive(philo))
		return (false);
	print_philo_state(philo, TAKE_FORK);
	if (!lock_fork(philo, philo_2) || !is_philo_alive(philo))
	{
		free_fork(philo_1);
		return (false);
	}
	print_philo_state(philo, TAKE_FORK);
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
	while (true)
	{
		if (!is_philo_alive(philo) || !all_philos_alive(philo))
			return (false);
		pthread_mutex_lock(&philo_to_lock->fork_free_mutex);
		if (philo_to_lock->fork_free)
		{
			philo_to_lock->fork_free = false;
			pthread_mutex_unlock(&philo_to_lock->fork_free_mutex);
			pthread_mutex_lock(&philo_to_lock->fork_mutex);
			return (true);
		}
		pthread_mutex_unlock(&philo_to_lock->fork_free_mutex);
	}
}

void	free_fork(t_philo *philo_to_free)
{
	pthread_mutex_lock(&philo_to_free->fork_free_mutex);
	pthread_mutex_unlock(&philo_to_free->fork_mutex);
	philo_to_free->fork_free = true;
	pthread_mutex_unlock(&philo_to_free->fork_free_mutex);
}
