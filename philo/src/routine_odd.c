/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_odd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:51:22 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/16 12:51:39 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_before_taking_forks(t_philo *philo);

void	*routine_odd(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_philosophers_to_be_ready(philo);
	store_start_time(philo);
	philo->last_meal_time = elapsed_time(philo);
	while (true)
	{
		make_odd_philos_wait(philo);
		if (!is_philo_alive(philo) || philo->table->simulation_over)
			break ;
		wait_before_taking_forks(philo);
		if (!take_forks(philo))
			break ;
		if (!philo_eat(philo))
			break ;
		return_forks(philo);
		if (!philo_sleep(philo))
			break ;
		if (!philo_think(philo))
			break ;
	}
	return (NULL);
}

static void	wait_before_taking_forks(t_philo *philo)
{
	int		end_time;

	if (philo->time_to_eat < philo->time_to_sleep)
		usleep(250);
	else if (elapsed_time(philo) - philo->last_meal_time > 50)
	{
		end_time = elapsed_time(philo) - 10 + philo->time_to_eat;
		while (end_time > elapsed_time(philo))
			usleep(PHILO_SLEEP_CYCLE_LENGTH);
	}
}
