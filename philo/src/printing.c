/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:29:13 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/14 12:55:53 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	print_state(t_philo *philo, int state);
static char	*make_str(int strlen, const char *ms_elapsed, const char *philo_n, int state);
static void	add_msg_to_str(char *str, int state);
static int	ft_strlen(const char *str);

void	print_philo_state(t_philo *philo, int state)
{
	if (philo->table->all_philosophers_alive
		&& !philo->table->all_finished_eating)
			print_state(philo, state);
}

static bool	print_state(t_philo *philo, int state)
{
	const char	*ms_elapsed = ft_itoa(elapsed_time(philo));
	const char	*philo_n = ft_itoa(philo->n);
	int			strlen;
	char		*str;

	if (!ms_elapsed || !philo_n)
		return (false);
	strlen = ft_strlen(ms_elapsed) + ft_strlen(philo_n) + 2;
	if (state == THINKING)
		strlen += 13;
	else if (state == EATING)
		strlen += 11;
	else if (state == TAKE_FORK)
		strlen += 18;
	else if (state == SLEEPING)
		strlen += 12;
	str = make_str(strlen, ms_elapsed, philo_n, state);
	write(1, str, strlen);
	return (true);
}

static char	*make_str(int strlen, const char *ms_elapsed, const char *philo_n, int state)
{
	char	*str;
	int		i;

	str = malloc(strlen);
	if (!str)
		return (NULL);
	i = 0;
	while (*ms_elapsed)
	{
		str[i] = *ms_elapsed;
		i++;
		ms_elapsed++;
	}
	str[i++] = ' '; 
	while (*philo_n)
	{
		str[i] = *philo_n;
		i++;
		philo_n++;
	}
	str[i++] = ' '; 
	add_msg_to_str(&str[i], state);
	return (str);
}

static void	add_msg_to_str(char *str, int state)
{
	const char	*thinking = "is thinking\n";
	const char	*eating = "is eating\n";
	const char	*take_fork = "has taken a fork\n";
	const char	*sleeping = "is sleeping\n";
	const char	*msg;

	if (state == THINKING)
		msg = thinking;
	if (state == EATING)
		msg = eating;
	if (state == TAKE_FORK)
		msg = take_fork;
	if (state == SLEEPING)
		msg = sleeping;
	while (*msg)
	{
		*str = *msg;
		str++;
		msg++;
	}
	*str = '\0';
}

static int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
