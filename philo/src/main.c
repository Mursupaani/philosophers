/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:42:46 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/06 17:01:56 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static t_table	*init_table(void);
static void		init_philosophers(t_table *table);
static void		init_forks_mutexes(t_table *table);
static void	start_routines(t_table *table);

int	main(int ac, char *av[])
{
	t_table		*table;

	if (ac < 5 || ac > 6)
		return (EXIT_FAILURE);
	table = init_table();
	parse_input_args(ac, av, table);
	init_philosophers(table);
	init_forks_mutexes(table);
	start_routines(table);
	free_app_memory(table);
	return (EXIT_SUCCESS);
}

static void	start_routines(t_table *table)
{
	int				i;
	struct timeval	time;

	i = 0;
	while (i < table->params[COUNT])
	{
		if (pthread_create(&table->philos[i].philo, NULL, &routine, &table->philos[i]))
			exit_failure(table);
		i++;
	}
	if (gettimeofday(&time, NULL))
		exit_failure(table);
	table->start_time = time.tv_usec;
	table->all_philosophers_ready = true;
}

static void	init_philosophers(t_table *table)
{
	int	i;

	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->params[COUNT]);
	if (!table->philos)
		exit_failure(table);
	i = 0;
	while (i < table->params[COUNT])
	{
		table->philos[i].time_to_die = table->params[TIME_TO_DIE];
		table->philos[i].time_to_eat = table->params[TIME_TO_EAT];
		table->philos[i].time_to_sleep = table->params[TIME_TO_SLEEP];
		table->philos[i].times_to_eat = table->params[TIMES_TO_EAT];
		table->philos[i].table = table;
		table->philos[i].index = i;
		if (i < table->params[COUNT] - 1)
			table->philos[i].index_next = i + 1;
		else
			table->philos[i].index_next = 0;
		table->num_of_philos_created++;
		i++;
	}
}

static void	init_forks_mutexes(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->alive_mutex, NULL))
		exit_failure(table);
	i = 0;
	while (i < table->num_of_philos_created)
	{
		if (pthread_mutex_init(&table->philos[i].fork_mutex, NULL))
			exit_failure(table);
		table->num_of_mutexes_created++;
		i++;
	}
}

static t_table	*init_table(void)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		exit(EXIT_FAILURE);
	memset(table, 0, sizeof(t_table));
	table->params[TIMES_TO_EAT] = -1;
	table->all_philosophers_alive = true;
	return (table);
}
