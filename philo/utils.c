/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:46:01 by cwick             #+#    #+#             */
/*   Updated: 2024/06/01 13:17:34 by cwick            ###   ########.fr       */
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
		error_exit(MAX_INT_ERR, NULL);
	return (result);
}

int	ft_usleep(__useconds_t time) // microseconds
{
	long	start;

	start = get_time(); // milliseconds
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 & *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
