/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:33:08 by anpollan          #+#    #+#             */
/*   Updated: 2025/04/22 15:33:09 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	count_int_digits(int n);

char	*ft_itoa(int n)
{
	char		*result;
	long int	num;
	int			end;

	end = count_int_digits(n);
	num = n;
	if (num < 0)
	{
		end++;
		num *= -1;
	}
	result = (char *)malloc(sizeof(char) * end + 1);
	if (!result)
		return (NULL);
	result[end--] = '\0';
	while (end >= 0)
	{
		if (n < 0 && end == 0)
			result[end] = '-';
		else
			result[end] = num % 10 + '0';
		num /= 10;
		end--;
	}
	return (result);
}

static int	count_int_digits(int n)
{
	int			len;

	if (n == 0)
		return (1);
	len = 0;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}
