/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 12:27:32 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/11 14:20:10 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_philosophers(t_table *table)
{
	int	i;

	table->philos
		= (t_philo *)malloc(sizeof(t_philo) * table->params[PHILO_COUNT]);
	if (!table->philos)
		return (false);
	i = -1;
	while (++i < table->params[PHILO_COUNT])
	{
		table->philos[i].time_to_die = table->params[TIME_TO_DIE];
		table->philos[i].time_to_eat = table->params[TIME_TO_EAT];
		table->philos[i].time_to_sleep = table->params[TIME_TO_SLEEP];
		table->philos[i].times_to_eat = table->params[TIMES_TO_EAT];
		table->philos[i].fork_free = true;
		table->philos[i].alive = true;
		table->philos[i].table = table;
		table->philos[i].index = i;
		table->philos[i].n = i + 1;
		if (i < table->params[PHILO_COUNT] - 1)
			table->philos[i].index_next = i + 1;
		else
			table->philos[i].index_next = 0;
		table->num_of_philos_created++;
	}
	return (true);
}

bool	init_philo_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->params[PHILO_COUNT])
	{
		if (pthread_mutex_init(&table->philos[i].fork_mutex, NULL))
			return (false);
		table->num_of_forks_mutexes_created++;
		if (pthread_mutex_init(&table->philos[i].fork_free_mutex, NULL))
			return (false);
		table->num_of_forks_free_mutexes_created++;
		if (pthread_mutex_init(&table->philos[i].alive_mutex, NULL))
			return (false);
		table->num_of_alive_mutexes_created++;
		if (pthread_mutex_init(&table->philos[i].finished_eating_mutex, NULL))
			return (false);
		table->num_of_finished_eating_mutexes_created++;
		i++;
	}
	return (true);
}

bool	init_table_mutexes(t_table *table)
{
	// if (pthread_mutex_init(&table->all_alive_mutex, NULL))
	// 	return (false);
	// table->all_alive_mutex_init = true;
	// if (pthread_mutex_init(&table->all_ready_mutex, NULL))
		// return (false);
	// table->all_ready_mutex_init = true;
	if (pthread_mutex_init(&table->time_mutex, NULL))
		return (false);
	table->time_mutex_init = true;
	// if (pthread_mutex_init(&table->all_finished_eating_mutex, NULL))
		// return (false);
	// table->all_finised_eating_mutex_init = true;
	return (true);
}

t_table	*init_table(void)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	memset(table, 0, sizeof(t_table));
	table->params[TIMES_TO_EAT] = -1;
	table->all_philosophers_alive = true;
	return (table);
}
