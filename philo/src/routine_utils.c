/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:27:49 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/06 16:28:47 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	elapsed_time(t_philo *philo)
{
	size_t	time;

	if (gettimeofday(&philo->time_now, NULL))
		return (-1);
	pthread_mutex_lock(&philo->table->time_mutex);
	time = philo->time_now.tv_sec * 1000
		+ philo->time_now.tv_usec / 1000
		- philo->table->start_time.tv_sec * 1000
		- philo->table->start_time.tv_usec / 1000;
	pthread_mutex_unlock(&philo->table->time_mutex);
	return (time);
}

int	ms_between_meals(t_philo *philo)
{
	int	time_now;
	int	ms_between_meals;

	time_now = elapsed_time(philo);
	ms_between_meals = time_now - philo->last_meal_time;
	return (ms_between_meals);
}

void	make_odd_philos_wait(t_philo *philo)
{
	if ((philo->index) % 2 == 0 && philo->index != philo->index_next)
		usleep(ODD_PHILO_WAIT_TIME);
}

void	wait_for_philosophers_to_be_ready(t_philo *philo)
{
	while (true)
	{
		pthread_mutex_lock(&philo->table->all_ready_mutex);
		if (philo->table->all_philosophers_ready)
		{
			pthread_mutex_unlock(&philo->table->all_ready_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->table->all_ready_mutex);
		usleep(200);
	}
}

bool	all_philos_alive(t_philo *philo)
{
	// pthread_mutex_lock(&philo->table->all_alive_mutex);
	if (philo->table->all_philosophers_alive)
	{
		// pthread_mutex_unlock(&philo->table->all_alive_mutex);
		return (true);
	}
	else
	{
		// pthread_mutex_unlock(&philo->table->all_alive_mutex);
		return (false);
	}
}
