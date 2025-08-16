/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:46:47 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/14 18:06:34 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_philo_alive(t_philo *philo)
{
	if (ms_between_meals(philo) >= philo->time_to_die)
	{
		philo->alive = false;
		return (false);
	}
	return (true);
}

void	update_eat_times_and_flag(t_philo *philo)
{
	philo->times_to_eat--;
	if (!philo->times_to_eat)
	{
		philo->finished_eating = true;
	}
}

void	check_death_during_sleeping(t_philo *philo)
{
	int	end_sleep;

	end_sleep = elapsed_time(philo) + philo->time_to_sleep;
	if (philo->time_to_sleep > 0)
	{
		while (is_philo_alive(philo) && !philo->table->simulation_over
			&& end_sleep > elapsed_time(philo))
			usleep(PHILO_SLEEP_CYCLE_LENGTH);
	}
}
