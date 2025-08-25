/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:29:13 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/14 18:04:24 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	add_msg_to_str(char *str, int state);
static int	ft_strlen(const char *str);

bool	print_philo_state(t_philo *philo, int state)
{
	char		buf[32];
	int			len;

	pthread_mutex_lock(&philo->table->print_mutex);
	len = ft_itoa_to_buf(elapsed_time(philo), buf, 32);
	buf[len++] = ' ';
	len += ft_itoa_to_buf(philo->n, &buf[len], 32 - len);
	buf[len++] = ' ';
	add_msg_to_str(&buf[len], state);
	if (is_philo_alive(philo) && !philo->table->simulation_over)
	{
		write(1, buf, ft_strlen(buf));
		pthread_mutex_unlock(&philo->table->print_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
	return (false);
}

static int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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
