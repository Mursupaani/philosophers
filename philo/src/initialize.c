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

#include "../incl/philo.h"

bool	init_philosophers(t_table *table)
{
	int	i;

	table->philos
		= (t_philo *)malloc(sizeof(t_philo) * table->params[PHILO_COUNT]);
	if (!table->philos)
		return (free_app_memory(table));
	i = -1;
	while (++i < table->params[PHILO_COUNT])
	{
		table->philos[i].time_to_die = table->params[TIME_TO_DIE];
		table->philos[i].time_to_eat = table->params[TIME_TO_EAT];
		table->philos[i].time_to_sleep = table->params[TIME_TO_SLEEP];
		table->philos[i].times_to_eat = table->params[TIMES_TO_EAT];
		table->philos[i].fork_free = true;
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

bool	init_forks_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->params[PHILO_COUNT])
	{
		if (pthread_mutex_init(&table->philos[i].fork_mutex, NULL))
		{
			free_app_memory(table);
			return (false);
		}
		table->num_of_forks_mutexes_created++;
		if (pthread_mutex_init(&table->philos[i].fork_free_mutex, NULL))
		{
			free_app_memory(table);
			return (false);
		}
		table->num_of_forks_free_mutexes_created++;
		i++;
	}
	return (true);
}

bool	init_table_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->all_alive_mutex, NULL))
	{
		free_app_memory(table);
		return (false);
	}
	table->all_alive_mutex_init = true;
	if (pthread_mutex_init(&table->all_ready_mutex, NULL))
	{
		free_app_memory(table);
		return (false);
	}
	table->all_ready_mutex_init = true;
	if (pthread_mutex_init(&table->time_mutex, NULL))
	{
		free_app_memory(table);
		return (false);
	}
	table->time_mutex_init = true;
	if (pthread_mutex_init(&table->finished_eating_mutex, NULL))
	{
		free_app_memory(table);
		return (false);
	}
	table->finised_eating_mutex_init = true;
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

bool	init_finished_eating_flags(t_table *table)
{
	size_t	size;

	if (!table)
		return (false);
	size = sizeof(bool) * table->params[PHILO_COUNT];
	table->finished_eating = (bool *)malloc(size);
	if (!table->finished_eating)
	{
		free_app_memory(table);
		return (false);
	}
	memset(table->finished_eating, 0, size);
	return (true);
}
