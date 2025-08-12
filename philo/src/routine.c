/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:55:27 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/11 13:25:52 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static bool	philo_think(t_philo *philo);
static bool	philo_sleep(t_philo *philo);
static bool	philo_eat(t_philo *philo);

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_philosophers_to_be_ready(philo);
	philo->last_meal_time = elapsed_time(philo);
	while (true)
	{
		make_odd_philos_wait(philo);
		if (!all_philos_alive(philo) || all_philosophers_ate_enough(philo))
			break ;
		if (!philo_eat(philo))
			break ;
		if (!philo_sleep(philo))
			break ;
		if (!philo_think(philo))
			break ;
	}
	return (NULL);
}

static bool	philo_think(t_philo *philo)
{
	if (!is_philo_alive(philo) || all_philosophers_ate_enough(philo))
		return (false);
	print_philo_state(philo, THINKING);
	return (true);
}

static bool	philo_eat(t_philo *philo)
{
	size_t	end_eat;

	if (!take_forks(philo))
		return (false);
	if (!is_philo_alive(philo) || all_philosophers_ate_enough(philo))
	{
		return_forks(philo);
		return (false);
	}
	print_philo_state(philo, EATING);
	if (philo->times_to_eat > 0)
		update_eat_times_and_flag(philo);
	end_eat = elapsed_time(philo) + philo->time_to_eat;
	philo->last_meal_time = elapsed_time(philo);
	while (all_philos_alive(philo) && end_eat > elapsed_time(philo))
		usleep(PHILO_SLEEP_CYCLE_LENGTH);
	return_forks(philo);
	return (true);
}

static bool	philo_sleep(t_philo *philo)
{
	if (!is_philo_alive(philo) || all_philosophers_ate_enough(philo))
		return (false);
	print_philo_state(philo, SLEEPING);
	check_death_during_sleeping(philo);
	return (true);
}
