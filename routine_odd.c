/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_odd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:55:27 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/14 18:36:08 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


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
		if (!take_forks(philo))
			break ;
		if (elapsed_time(philo) - philo->last_meal_time)
			sleep_until(philo, elapsed_time(philo) - 2 + philo->times_to_eat);
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
