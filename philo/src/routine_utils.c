/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:27:49 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/14 18:10:04 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	elapsed_time(t_philo *philo)
{
	int	time;

	if (gettimeofday(&philo->time_now, NULL))
		return (-1);
	time = philo->time_now.tv_sec * 1000
		+ philo->time_now.tv_usec / 1000
		- philo->start_time.tv_sec * 1000
		- philo->start_time.tv_usec / 1000;
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

void	make_even_philos_wait(t_philo *philo)
{
	if ((philo->n) % 2 == 0)
		usleep(PHILO_WAIT_TIME);
}

bool	wait_for_philosophers_to_be_ready(t_philo *philo)
{
	while (true)
	{
		if (philo->table->all_philosophers_ready)
			return (true);
		if (philo->table->simulation_over)
			return (false);
		usleep(200);
	}
}
