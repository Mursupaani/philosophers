/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:42:46 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/07 15:44:14 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static bool	start_routines(t_table *table);

int	main(int ac, char *av[])
{
	t_table		*table;
	int			exit_status;

	if (ac < 5 || ac > 6)
		return (EXIT_FAILURE);
	table = init_table();
	if (!table)
		return (EXIT_FAILURE);
	if (!parse_input_args(ac, av, table))
		return (EXIT_FAILURE);
	if (!init_philosophers(table))
		return (EXIT_FAILURE);
	if (!init_forks_mutexes(table))
		return (EXIT_FAILURE);
	if (!start_routines(table))
		return (EXIT_FAILURE);
	if (observer_routine(table))
		exit_status = EXIT_SUCCESS;
	else
		exit_status = EXIT_FAILURE;
	free_app_memory(table);
	return (exit_status);
}

static bool	start_routines(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->params[COUNT])
	{
		if (pthread_create(&table->philos[i].philo, NULL, &routine, &table->philos[i]))
		{
			free_app_memory(table);
			return (false);
		}
		i++;
	}
	if (gettimeofday(&table->start_time, NULL))
	{
		free_app_memory(table);
		return (false);
	}
	pthread_mutex_lock(&table->all_ready_mutex);
	table->all_philosophers_ready = true;
	pthread_mutex_unlock(&table->all_ready_mutex);
	return (true);
}
