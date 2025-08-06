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

void	exit_failure(t_app *app)
{
	free_app_memory(app);
	exit(EXIT_FAILURE);
}

void	free_app_memory(t_app *app)
{
	if (!app)
		return ;
	if (app->philos)
		free(app->philos);
	if (app->forks_mutexes)
		free(app->forks_mutexes);
	free(app);
}

void	join_philosophers_to_main(t_app *app)
{
	int	i;

	if (!app && !app->philos)
		return ;
	i = 0;
	while (i < app->params[PHILOS_COUNT])
	{
		if (pthread_join(app->philos[i], NULL))
			exit_failure(app);
		i++;
	}
}

void	destroy_forks_mutexes(t_app *app)
{
	int	i;

	if (!app && !app->forks_mutexes)
		return ;
	i = 0;
	while (i < app->params[PHILOS_COUNT])
	{
		if (pthread_mutex_destroy(&app->forks_mutexes[i]))
			exit_failure(app);
		i++;
	}
}
