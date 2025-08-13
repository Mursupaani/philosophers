/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:29:31 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/07 15:41:57 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"
#include <pthread.h>

static bool	all_philos_finished_eating(t_table *table);
static bool	all_philos_still_alive(t_table *table);
static void	print_philo_dead(t_philo *philo);

bool	observer_routine(t_table *table)
{
	if (!table)
		return (false);
	if (table->num_of_philos_created != table->num_of_threads_created)
	{
		pthread_mutex_lock(&table->all_alive_mutex);
		table->all_philosophers_alive = false;
		pthread_mutex_unlock(&table->all_alive_mutex);
		return (false);
	}
	while (true)
	{
		if (!all_philos_still_alive(table))
			return (true);
		if (table->params[TIMES_TO_EAT] != -1
			&& all_philos_finished_eating(table))
			return (true);
		usleep(1);
	}
}

static bool	all_philos_finished_eating(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->finished_eating_mutex);
	while (i < table->num_of_philos_created)
	{
		if (!table->finished_eating[i])
		{
			pthread_mutex_unlock(&table->finished_eating_mutex);
			return (false);
		}
		i++;
	}
	table->all_finished_eating = true;
	pthread_mutex_unlock(&table->finished_eating_mutex);
	return (true);
}

static bool	all_philos_still_alive(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos_created)
	{
		pthread_mutex_lock(&table->philos[i].alive_mutex);
		if (!table->philos[i].alive)
		{
			pthread_mutex_lock(&table->all_alive_mutex);
			table->all_philosophers_alive = false;
			pthread_mutex_unlock(&table->philos[i].alive_mutex);
			pthread_mutex_unlock(&table->all_alive_mutex);
			print_philo_dead(&table->philos[i]);
			return (false);
		}
		pthread_mutex_unlock(&table->philos[i].alive_mutex);
		i++;
	}
	return (true);
}

static void	print_philo_dead(t_philo *philo)
{
	printf("%lu %d died\n", elapsed_time(philo), philo->n);
}

// static bool	all_philos_still_alive(t_table *table)
// {
// 	pthread_mutex_lock(&table->all_alive_mutex);
// 	pthread_mutex_lock(&table->a_philo_is_dead_mutex);
// 	if (table->a_philo_is_dead)
// 	{
// 		table->all_philosophers_alive = false;
// 		pthread_mutex_unlock(&table->all_alive_mutex);
// 		pthread_mutex_unlock(&table->a_philo_is_dead_mutex);
// 		return (false);
// 	}
// 	pthread_mutex_unlock(&table->all_alive_mutex);
// 	pthread_mutex_unlock(&table->a_philo_is_dead_mutex);
// 	return (true);
// }
