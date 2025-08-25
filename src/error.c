/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:34:56 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/14 12:39:58 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error_and_free_memory(t_table *table, int error)
{
	if (error == ERR_ARG_COUNT)
		ft_putstr_fd("Error arg count\n", STDERR_FILENO);
	else if (error == ERR_INIT_TABLE)
		ft_putstr_fd("Error initializing table\n", STDERR_FILENO);
	else if (error == ERR_PARSING)
		ft_putstr_fd("Error parsing. Use only positive numeric values\n",
			STDERR_FILENO);
	else if (error == ERR_EAT_TIMES)
		ft_putstr_fd("Error eat times. Use values above 0\n", STDERR_FILENO);
	else if (error == ERR_PHILO_COUNT)
		ft_putstr_fd("Error in philo count. Use only numbers 1-500\n",
			STDERR_FILENO);
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
