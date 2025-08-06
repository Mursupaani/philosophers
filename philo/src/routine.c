/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:55:27 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/06 11:59:48 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	*philo_routine(void *arg)
{
	struct timeval	time;
	t_app			*app;

	app = (t_app *)arg;
	if (gettimeofday(&time, NULL))
		exit_failure(app);
	return (NULL);
}
