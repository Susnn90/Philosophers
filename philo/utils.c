/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:46:01 by cwick             #+#    #+#             */
/*   Updated: 2024/05/20 12:22:14 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	i;
	long	result;

	i = 0;
	result = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == '+' || str[i] == ' ')
		{
			i++;
			continue ;
		}
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	if (result > INT_MAX)
		error_exit(MAX_INT_ERR);
	return (result);
}
void	error_exit(const char *error)
{
	printf("%s\n", error);
	exit (EXIT_FAILURE);
}
