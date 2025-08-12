/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:57:05 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/11 14:20:03 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static void	destroy_forks_mutexes(t_table *table);
static void	join_philosophers_to_main(t_table *table);
static void	destroy_table_mutexes(t_table *table);

bool	free_app_memory(t_table *table)
{
	if (!table)
		return (false);
	join_philosophers_to_main(table);
	destroy_forks_mutexes(table);
	destroy_table_mutexes(table);
	if (table->philos)
		free(table->philos);
	if (table->finished_eating)
		free(table->finished_eating);
	free(table);
	return (false);
}

static void	join_philosophers_to_main(t_table *table)
{
	int	i;

	if (!table && !table->philos)
		return ;
	i = 0;
	while (i < table->num_of_threads_created)
	{
		if (pthread_join(table->philos[i].philo, NULL))
			printf("Failed to join philo #%d\n", i + 1);
		i++;
	}
}

static void	destroy_forks_mutexes(t_table *table)
{
	int	i;

	if (!table && !table->philos)
		return ;
	i = 0;
	while (i < table->num_of_forks_mutexes_created)
	{
		if (pthread_mutex_destroy(&table->philos[i].fork_mutex))
			printf("Failed to destroy fork mutex #%d\n", i + 1);
		i++;
	}
	while (i < table->num_of_forks_free_mutexes_created)
	{
		if (pthread_mutex_destroy(&table->philos[i].fork_free_mutex))
			printf("Failed to destroy fork free mutex #%d\n", i + 1);
		i++;
	}
}

static void	destroy_table_mutexes(t_table *table)
{
	if (!table)
		return ;
	if (table->all_alive_mutex_init
		&& pthread_mutex_destroy(&table->all_alive_mutex))
		printf("Failed to destroy all alive mutex\n");
	if (table->all_ready_mutex_init
		&& pthread_mutex_destroy(&table->all_ready_mutex))
		printf("Failed to destroy all ready mutex\n");
	if (table->time_mutex_init
		&& pthread_mutex_destroy(&table->time_mutex))
		printf("Failed to destroy time mutex\n");
	if (table->finised_eating_mutex_init
		&& pthread_mutex_destroy(&table->finished_eating_mutex))
		printf("Failed to destroy finished eating mutex\n");
}
