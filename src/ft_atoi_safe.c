/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_safe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:52:59 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/06 10:33:11 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(char c);

int	*ft_atoi_safe(const char *nptr)
{
	static long int	res[1];

	*res = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+')
	{
		nptr++;
		if (!ft_isdigit(*nptr))
			return (NULL);
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		*res *= 10;
		*res += *nptr - '0';
		nptr++;
	}
	if (*res <= INT_MAX && (*nptr == '\0' || *nptr == '\n'))
		return ((int *)res);
	return (NULL);
}

static int	ft_isdigit(char c)
{
	return (c <= '9' && c >= '0');
}
