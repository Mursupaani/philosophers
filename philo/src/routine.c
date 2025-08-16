/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:55:27 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/14 18:49:14 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_even(void *arg)
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

bool	philo_think(t_philo *philo)
{
	if (!print_philo_state(philo, THINKING))
		return (false);
	return (true);
}

bool	philo_eat(t_philo *philo)
{
	int	end_time;

	if (!is_philo_alive(philo))
	{
		return_forks(philo);
		return (false);
	}
	print_philo_state(philo, EATING);
	if (philo->times_to_eat > 0)
		update_eat_times_and_flag(philo);
	end_time = elapsed_time(philo) + philo->time_to_eat;
	philo->last_meal_time = elapsed_time(philo);
	while (!philo->table->simulation_over && end_time > elapsed_time(philo))
		usleep(PHILO_SLEEP_CYCLE_LENGTH);
	return (true);
}

bool	philo_sleep(t_philo *philo)
{
	if (!print_philo_state(philo, SLEEPING))
		return (false);
	check_death_during_sleeping(philo);
	return (true);
}

void	store_start_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->time_mutex);
	philo->start_time.tv_sec = philo->table->start_time.tv_sec;
	philo->start_time.tv_usec = philo->table->start_time.tv_usec;
	pthread_mutex_unlock(&philo->table->time_mutex);
}
