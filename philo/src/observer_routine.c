/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:29:31 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/14 12:56:19 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		usleep(10);
	}
}

static bool	all_philos_finished_eating(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos_created)
	{
		if (!table->philos[i].finished_eating)
			return (false);
		i++;
	}
	pthread_mutex_lock(&table->all_finished_eating_mutex);
	table->all_finished_eating = true;
	pthread_mutex_unlock(&table->all_finished_eating_mutex);
	return (true);
}

static bool	all_philos_still_alive(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos_created)
	{
		if (!table->philos[i].alive)
		{
			pthread_mutex_lock(&table->all_alive_mutex);
			table->all_philosophers_alive = false;
			pthread_mutex_unlock(&table->all_alive_mutex);
			print_philo_dead(&table->philos[i]);
			return (false);
		}
		i++;
	}
	return (true);
}

static void	print_philo_dead(t_philo *philo)
{
	printf("%d %d died\n", elapsed_time(philo), philo->n);
}
