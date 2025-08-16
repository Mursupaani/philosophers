/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:42:46 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/14 18:49:30 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	start_routines(t_table *table);
static bool	start_simulation_clock(t_table *table);

int	main(int ac, char *av[])
{
	t_table		*table;

	if (ac < 5 || ac > 6)
		return (print_error_and_free_memory(NULL, ERR_ARG_COUNT));
	table = init_table();
	if (!table)
		return (print_error_and_free_memory(table, ERR_INIT_TABLE));
	if (!parse_input_args(ac, av, table))
		return (print_error_and_free_memory(table, ERR_PARSING));
	if (table->params[TIMES_TO_EAT] == 0)
		return (print_error_and_free_memory(table, ERR_EAT_TIMES));
	if (table->params[PHILO_COUNT] > MAX_PHILOS || !table->params[PHILO_COUNT])
		return (print_error_and_free_memory(table, ERR_PHILO_COUNT));
	if (!init_philosophers(table))
		return (print_error_and_free_memory(table, ERR_INIT_PHILO));
	if (!init_philo_mutexes(table) || !init_table_mutexes(table))
		return (print_error_and_free_memory(table, ERR_INIT_MUTEXES));
	if (!start_routines(table))
		return (print_error_and_free_memory(table, ERR_PHILO_THREADS));
	if (!routine_observer(table))
		return (print_error_and_free_memory(table, ERR_OBSERVER_THREAD));
	free_app_memory(table);
	return (EXIT_SUCCESS);
}

static bool	start_routines(t_table *table)
{
	int		i;
	void	*routine;

	if (table->params[PHILO_COUNT] % 2 == 0)
		routine = &routine_even;
	else
		routine = &routine_odd;
	i = 0;
	while (i < table->params[PHILO_COUNT])
	{
		if (pthread_create(&table->philos[i].philo, NULL,
				routine, &table->philos[i]))
		{
			free_app_memory(table);
			return (false);
		}
		table->num_of_threads_created++;
		i++;
	}
	if (!start_simulation_clock(table))
		return (false);
	return (true);
}

static bool	start_simulation_clock(t_table *table)
{
	pthread_mutex_lock(&table->time_mutex);
	if (gettimeofday(&table->start_time, NULL))
	{
		table->simulation_over = true;
		free_app_memory(table);
		return (false);
	}
	pthread_mutex_unlock(&table->time_mutex);
	table->all_philosophers_ready = true;
	return (true);
}
