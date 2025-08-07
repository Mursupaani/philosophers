/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:55:27 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/07 15:44:36 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static void	p_think(t_philo *philo);
static void	p_sleep(t_philo *philo);
static void	p_eat(t_philo *philo);
static bool	is_philo_alive(t_philo *philo);

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		pthread_mutex_lock(&philo->table->all_ready_mutex);
		if (philo->table->all_philosophers_alive)
		{
			pthread_mutex_unlock(&philo->table->all_ready_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->table->all_ready_mutex);
		usleep(200);
	}
	usleep(200);
	philo->last_meal_time = elapsed_time(philo);
	while (true)
	{
		pthread_mutex_lock(&philo->table->all_alive_mutex);
		if (!philo->times_to_eat || !philo->table->all_philosophers_alive)
		{
			pthread_mutex_unlock(&philo->table->all_alive_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->table->all_alive_mutex);
		p_think(philo);
		is_philo_alive(philo);
		p_eat(philo);
		is_philo_alive(philo);
		p_sleep(philo);
		is_philo_alive(philo);
	}
	printf("%d exiting\n", philo->index + 1);
	return (NULL);
}

static void	p_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->all_alive_mutex);
	if (philo->table->all_philosophers_alive)
		printf("%lu %d is thinking\n", elapsed_time(philo), philo->index + 1);
	pthread_mutex_unlock(&philo->table->all_alive_mutex);
}

static void	p_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->all_alive_mutex);
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_mutex);
		is_philo_alive(philo);
		if (philo->table->all_philosophers_alive)
			printf("%lu %d has taken a fork\n", elapsed_time(philo), philo->index + 1);
		is_philo_alive(philo);
		pthread_mutex_lock(&philo->table->philos[philo->index_next].fork_mutex);
		if (philo->table->all_philosophers_alive)
			printf("%lu %d has taken a fork\n", elapsed_time(philo), philo->index + 1);
	}
	else
	{
		pthread_mutex_lock(&philo->table->philos[philo->index_next].fork_mutex);
		if (philo->table->all_philosophers_alive)
			printf("%lu %d has taken a fork\n", elapsed_time(philo), philo->index + 1);
		pthread_mutex_lock(&philo->fork_mutex);
		if (philo->table->all_philosophers_alive)
			printf("%lu %d has taken a fork\n", elapsed_time(philo), philo->index + 1);
	}
	if (philo->table->all_philosophers_alive)
	{
		printf("%lu %d is eating\n", elapsed_time(philo), philo->index + 1);
		usleep(philo->time_to_eat);
		philo->last_meal_time = elapsed_time(philo);
	}
	if (philo->index % 2 == 0)
	{
		pthread_mutex_unlock(&philo->table->philos[philo->index_next].fork_mutex);
		pthread_mutex_unlock(&philo->fork_mutex);
	}
	else
	{
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(&philo->table->philos[philo->index_next].fork_mutex);
	}
	pthread_mutex_unlock(&philo->table->all_alive_mutex);
	if (philo->times_to_eat != -1)
		philo->times_to_eat--;
}

static void	p_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->all_alive_mutex);
	if (philo->table->all_philosophers_alive)
	{
		printf("%lu %d is sleeping\n", elapsed_time(philo), philo->index + 1);
		usleep(philo->time_to_sleep);
	}
	pthread_mutex_unlock(&philo->table->all_alive_mutex);
}

static bool	is_philo_alive(t_philo *philo)
{
	if (ms_between_meals(philo) >= philo->time_to_die)
	{
		pthread_mutex_lock(&philo->table->all_alive_mutex);
		if (philo->table->all_philosophers_alive)
		{
			philo->table->all_philosophers_alive = false;
			printf("%lu %d died\n", elapsed_time(philo), philo->index + 1);
			return (false);
		}
		pthread_mutex_unlock(&philo->table->all_alive_mutex);
	}
	return (true);
}
