/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:55:27 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/07 16:59:48 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static bool	p_think(t_philo *philo);
static bool	p_sleep(t_philo *philo);
static bool	p_eat(t_philo *philo);

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_for_philosophers_to_be_ready(philo);
	philo->last_meal_time = elapsed_time(philo);
	make_even_philos_wait(philo);
	while (true)
	{
		if (!philo->times_to_eat || !all_philos_alive(philo))
			break ;
		if (!p_think(philo))
			break ;
		if (!p_eat(philo))
			break ;
		if (!p_sleep(philo))
			break ;
		if (philo->n == 20)
		{
			pthread_mutex_lock(&philo->table->all_alive_mutex);
			philo->table->all_philosophers_alive = false;
			pthread_mutex_unlock(&philo->table->all_alive_mutex);
		}
	}
	update_finished_eating_flag(philo);
	return (NULL);
}

static bool	p_think(t_philo *philo)
{
	if (!is_philo_alive(philo))
		return (false);
	print_philo_state(philo, THINKING);
	return (true);
}

static bool	p_eat(t_philo *philo)
{
	take_forks(philo);
	if (!is_philo_alive(philo))
	{
		return_forks(philo);
		return (false);
	}
	print_philo_state(philo, EATING);
	usleep(philo->time_to_eat);
	philo->last_meal_time = elapsed_time(philo);
	return_forks(philo);
	if (philo->times_to_eat != -1)
		philo->times_to_eat--;
	return (true);
}

static bool	p_sleep(t_philo *philo)
{
	if (!is_philo_alive(philo))
		return (false);
	print_philo_state(philo, SLEEPING);
	usleep(philo->time_to_sleep);
	return (true);
}
