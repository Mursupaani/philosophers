/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:55:27 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/06 17:10:22 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static void			p_think(t_philo *philo, struct timeval time);
static void			p_sleep(t_philo *philo, struct timeval time);
static useconds_t	p_eat(t_philo *philo, struct timeval time);
static bool			is_philo_dead(t_philo *philo, struct timeval time);

void	*routine(void *arg)
{
	t_philo			*philo;
	struct timeval	time;

	philo = (t_philo *)arg;
	philo->last_meal_time = time_now(&time, philo);
	while (!philo->table->all_philosophers_ready)
		usleep(200);
	while (philo->times_to_eat && philo->table->all_philosophers_alive)
	{
		pthread_mutex_unlock(&philo->table->alive_mutex);
		is_philo_dead(philo, time);
		p_think(philo, time);
		is_philo_dead(philo, time);
		p_eat(philo, time);
		is_philo_dead(philo, time);
		p_sleep(philo, time);
		pthread_mutex_lock(&philo->table->alive_mutex);
	}
	return (NULL);
}

static void	p_think(t_philo *philo, struct timeval time)
{
	if (philo->table->all_philosophers_alive)
		printf("%ld %d is thinking\n", time_now(&time, philo), philo->index + 1);
	usleep(philo->time_to_sleep);
}

static useconds_t	p_eat(t_philo *philo, struct timeval time)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_mutex);
		if (philo->table->all_philosophers_alive)
			printf("%ld %d has taken a fork\n", time_now(&time, philo), philo->index + 1);
		pthread_mutex_lock(&philo->table->philos[philo->index_next].fork_mutex);
		if (philo->table->all_philosophers_alive)
			printf("%ld %d has taken a fork\n", time_now(&time, philo), philo->index + 1);
	}
	else
	{
		pthread_mutex_lock(&philo->table->philos[philo->index_next].fork_mutex);
		if (philo->table->all_philosophers_alive)
			printf("%ld %d has taken a fork\n", time_now(&time, philo), philo->index + 1);
		pthread_mutex_lock(&philo->fork_mutex);
		if (philo->table->all_philosophers_alive)
			printf("%ld %d has taken a fork\n", time_now(&time, philo), philo->index + 1);
	}
	if (philo->table->all_philosophers_alive)
	{
		printf("%ld %d has taken a fork\n", time_now(&time, philo), philo->index + 1);
		printf("%ld %d is eating\n", time_now(&time, philo), philo->index + 1);
		usleep(philo->time_to_eat);
		philo->last_meal_time = time_now(&time, philo);
	}
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_unlock(&philo->table->philos[philo->index_next].fork_mutex);
	if (philo->times_to_eat != -1)
		philo->times_to_eat--;
	return (0);
}

static void	p_sleep(t_philo *philo, struct timeval time)
{
	if (philo->table->all_philosophers_alive)
	{
		printf("%ld %d is sleeping\n", time_now(&time, philo), philo->index + 1);
		usleep(philo->time_to_sleep);
	}
}

static bool	is_philo_dead(t_philo *philo, struct timeval time)
{
	if (time_now(&time, philo) - philo->last_meal_time >= philo->time_to_die)
	{
		pthread_mutex_lock(&philo->table->alive_mutex);
		if (philo->table->all_philosophers_alive)
		{
			philo->table->all_philosophers_alive = false;
			printf("%ld %d died\n", time.tv_usec, philo->index + 1);
		}
		pthread_mutex_unlock(&philo->table->alive_mutex);
	}
	return (false);
}
