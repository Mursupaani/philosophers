/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:46:47 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/11 14:56:12 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

bool	is_philo_alive(t_philo *philo)
{
	if (ms_between_meals(philo) >= philo->time_to_die)
	{
		pthread_mutex_lock(&philo->alive_mutex);
		philo->alive = false;
		pthread_mutex_unlock(&philo->alive_mutex);
		return (false);
	}
	return (true);
}

// bool	is_philo_alive(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->table->all_alive_mutex);
// 	if (ms_between_meals(philo) >= philo->time_to_die
// 		|| !philo->table->all_philosophers_alive)
// 	{
// 		if (philo->table->all_philosophers_alive)
// 		{
// 			pthread_mutex_unlock(&philo->table->all_alive_mutex);
// 			print_philo_state(philo, DEAD);
// 			return (false);
// 		}
// 		pthread_mutex_unlock(&philo->table->all_alive_mutex);
// 		return (false);
// 	}
// 	pthread_mutex_unlock(&philo->table->all_alive_mutex);
// 	return (true);
// }

void	update_eat_times_and_flag(t_philo *philo)
{
	philo->times_to_eat--;
	if (!philo->times_to_eat)
	{
		pthread_mutex_lock(&philo->table->finished_eating_mutex);
		philo->table->finished_eating[philo->index] = true;
		pthread_mutex_unlock(&philo->table->finished_eating_mutex);
	}
}

void	check_death_during_sleeping(t_philo *philo)
{
	size_t	end_sleep;

	end_sleep = elapsed_time(philo) + philo->time_to_sleep;
	if (philo->time_to_sleep > 0)
	{
		while (is_philo_alive(philo) && all_philos_alive(philo)
			&& end_sleep > elapsed_time(philo))
			usleep(PHILO_SLEEP_CYCLE_LENGTH);
	}
}

bool	all_philosophers_ate_enough(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->finished_eating_mutex);
	if (philo->table->all_finished_eating)
	{
		pthread_mutex_unlock(&philo->table->finished_eating_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->table->finished_eating_mutex);
	return (false);
}
