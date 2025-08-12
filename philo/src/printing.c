/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:29:13 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/11 13:28:04 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"
#include <stdlib.h>
#include <unistd.h>

void	print_philo_state(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->table->all_alive_mutex);
	pthread_mutex_lock(&philo->table->finished_eating_mutex);
	if (philo->table->all_philosophers_alive
		&& !philo->table->all_finished_eating)
	{
		if (state == THINKING)
			printf("%lu %d is thinking\n", elapsed_time(philo), philo->n);
		else if (state == EATING)
			printf("%lu %d is eating\n", elapsed_time(philo), philo->n);
		else if (state == TAKE_FORK)
			printf("%lu %d has taken a fork\n", elapsed_time(philo), philo->n);
		else if (state == SLEEPING)
			printf("%lu %d is sleeping\n", elapsed_time(philo), philo->n);
		else if (state == DEAD)
		{
			philo->table->all_philosophers_alive = false;
			printf("%lu %d died\n", elapsed_time(philo), philo->n);
		}
	}
	pthread_mutex_unlock(&philo->table->all_alive_mutex);
	pthread_mutex_unlock(&philo->table->finished_eating_mutex);
}

int	free_memory_and_print_error_message(t_table *table, int error)
{
	if (error == ERR_ARG_COUNT)
		ft_putstr_fd("Error arg count\n", STDERR_FILENO);
	if (error == ERR_INIT_TABLE)
		ft_putstr_fd("Error initializing table\n", STDERR_FILENO);
	else if (error == ERR_PARSING)
		ft_putstr_fd("Error parsing\n", STDERR_FILENO);
	else if (error == ERR_INIT_PHILO)
		ft_putstr_fd("Error initializing philosophers\n", STDERR_FILENO);
	else if (error == ERR_INIT_MUTEXES)
		ft_putstr_fd("Error initializing mutexes\n", STDERR_FILENO);
	else if (error == ERR_INIT_FINISH_EAT)
		ft_putstr_fd("Error initializing finish eating flags\n", STDERR_FILENO);
	else if (error == ERR_PHILO_THREADS)
		ft_putstr_fd("Error creating philo threads\n", STDERR_FILENO);
	else if (error == ERR_OBSERVER_THREAD)
		ft_putstr_fd("Error in observer thread\n", STDERR_FILENO);
	if (table)
		free_app_memory(table);
	return (EXIT_FAILURE);
}
