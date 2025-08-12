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

static bool	all_philos_finished_eating(t_table *table);

bool	observer_routine(t_table *table)
{
	if (table->num_of_philos_created != table->num_of_threads_created)
	{
		pthread_mutex_lock(&table->all_alive_mutex);
		table->all_philosophers_alive = false;
		pthread_mutex_unlock(&table->all_alive_mutex);
		return (false);
	}
	while (true)
	{
		pthread_mutex_lock(&table->all_alive_mutex);
		if (!table->all_philosophers_alive)
		{
			pthread_mutex_unlock(&table->all_alive_mutex);
			return (true);
		}
		pthread_mutex_unlock(&table->all_alive_mutex);
		if (table->params[TIMES_TO_EAT] != -1
			&& all_philos_finished_eating(table))
			return (true);
		usleep(1000);
	}
}

static bool	all_philos_finished_eating(t_table *table)
{
	int	i;

	if (!table)
		return (false);
	i = 0;
	while (i < table->num_of_philos_created)
	{
		pthread_mutex_lock(&table->finished_eating_mutex);
		if (!table->finished_eating[i])
		{
			pthread_mutex_unlock(&table->finished_eating_mutex);
			return (false);
		}
		pthread_mutex_unlock(&table->finished_eating_mutex);
		i++;
	}
	pthread_mutex_lock(&table->finished_eating_mutex);
	table->all_finished_eating = true;
	pthread_mutex_unlock(&table->finished_eating_mutex);
	return (true);
}
