/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:29:31 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/14 18:19:47 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	all_philos_finished_eating(t_table *table);
static bool	all_philos_still_alive(t_table *table);
static void	print_philo_dead(t_philo *philo, t_table *table);
static int	elapsed_time_observer(t_table *table);

bool	observer_routine(t_table *table)
{
	if (!table)
		return (false);
	if (table->num_of_philos_created != table->num_of_threads_created)
	{
		table->simulation_over = true;
		return (false);
	}
	while (true)
	{
		if (!all_philos_still_alive(table))
			return (true);
		if (table->params[TIMES_TO_EAT] != -1
			&& all_philos_finished_eating(table))
			return (true);
		usleep(1000);
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
	table->simulation_over = true;
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
			table->simulation_over = true;
			print_philo_dead(&table->philos[i], table);
			return (false);
		}
		i++;
	}
	return (true);
}

static void	print_philo_dead(t_philo *philo, t_table *table)
{
	int	elapsed_time;

	elapsed_time = elapsed_time_observer(table);
	usleep(2000);
	printf("%d %d died\n", elapsed_time, philo->n);
}

static int	elapsed_time_observer(t_table *table)
{
	int				time;
	struct timeval	time_now;

	if (gettimeofday(&time_now, NULL))
		return (-1);
	time = time_now.tv_sec * 1000
		+ time_now.tv_usec / 1000
		- table->start_time.tv_sec * 1000
		- table->start_time.tv_usec / 1000;
	return (time);
}
