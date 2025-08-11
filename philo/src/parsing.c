/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 09:37:43 by anpollan          #+#    #+#             */
/*   Updated: 2025/08/06 10:26:19 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

bool	parse_input_args(int ac, char **av, t_table *table)
{
	int	*temp;
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		temp = ft_atoi_safe(av[i]);
		if (!temp)
		{
			free_app_memory(table);
			return (false);
		}
		table->params[j] = *temp;
		i++;
		j++;
	}
	return (true);
}
