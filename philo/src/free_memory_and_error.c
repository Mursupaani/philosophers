/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_and_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:57:05 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/06 12:28:19 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	exit_failure(t_table *table)
{
	free_app_memory(table);
	exit(EXIT_FAILURE);
}

void	free_app_memory(t_table *table)
{
	if (!table)
		return ;
	join_philosophers_to_main(table);
	destroy_forks_mutexes(table);
	if (table->philos)
		free(table->philos);
	free(table);
}

void	join_philosophers_to_main(t_table *table)
{
	int	i;

	if (!table && !table->philos)
		return ;
	i = 0;
	while (i < table->num_of_philos_created)
	{
		if (pthread_join(table->philos[i].philo, NULL))
			printf("Failed to join philo #%d\n", i + 1);
		i++;
	}
}

void	destroy_forks_mutexes(t_table *table)
{
	int	i;

	if (!table && !table->philos)
		return ;
	i = 0;
	while (i < table->num_of_mutexes_created)
	{
		if (pthread_mutex_destroy(&table->philos[i].fork_mutex))
			printf("Failed to destroy fork mutex #%d\n", i + 1);
		i++;
	}
}
