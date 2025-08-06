/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:42:46 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/06 12:32:28 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"
#include <pthread.h>

static t_app	*init_app(void);
static void		init_philosophers(t_app *app);
static void		init_forks_mutexes(t_app *app);

int	main(int ac, char *av[])
{
	t_app		*app;

	if (ac < 5 || ac > 6)
		return (EXIT_FAILURE);
	app = init_app();
	parse_input_args(ac, av, app);
	init_forks_mutexes(app);
	init_philosophers(app);
	join_philosophers_to_main(app);
	destroy_forks_mutexes(app);
	free_app_memory(app);
	return (EXIT_SUCCESS);
}

static void	init_philosophers(t_app *app)
{
	int	i;
	app->philos = (pthread_t *)malloc(sizeof(pthread_t) * app->params[PHILOS_COUNT]);
	if (!app->philos)
		exit_failure(app);
	i = 0;
	while (i < app->params[PHILOS_COUNT])
	{
		if (pthread_create(&app->philos[i], NULL, &philo_routine, app))
			exit_failure(app);
		i++;
	}
}

static void	init_forks_mutexes(t_app *app)
{
	int	i;

	app->forks_mutexes = malloc(sizeof(pthread_mutex_t) * app->params[PHILOS_COUNT]);
	if (!app->forks_mutexes)
		exit_failure(app);
	i = 0;
	while (i < app->params[PHILOS_COUNT])
	{
		if (pthread_mutex_init(&app->forks_mutexes[i], NULL))
			exit_failure(app);
		i++;
	}
}

static t_app	*init_app(void)
{
	t_app	*app;

	app = (t_app *)malloc(sizeof(t_app));
	if (!app)
		exit(EXIT_FAILURE);
	memset(app, 0, sizeof(t_app));
	app->params[TIMES_TO_EAT] = -1;
	app->all_philosophers_alive = true;
	return (app);
}
