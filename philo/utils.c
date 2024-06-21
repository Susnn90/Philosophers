/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:46:01 by cwick             #+#    #+#             */
/*   Updated: 2024/06/21 13:58:18 by cwick            ###   ########.fr       */
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

int	ft_usleep(__useconds_t time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(100);
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
	return (0);
}

void	print_action(char *str, t_philo *philos, long time)
{
	if (philos->data->dead == 0)
	{
		pthread_mutex_lock(&philos->data->write);
		time = get_time() - philos->data->start_time;
		if (ft_strcmp(EATING, str) == 0)
			printf("%s%ld %ld %s%s\n", G, time, philos->id, str, RST);
		else if (ft_strcmp(SLEEPING, str) == 0)
			printf("%s%ld %ld %s%s\n", C, time, philos->id, str, RST);
		else if (ft_strcmp(THINKING, str) == 0)
			printf("%s%ld %ld %s%s\n", Y, time, philos->id, str, RST);
		else
			printf("%ld %ld %s\n", time, philos->id, str);
		pthread_mutex_unlock(&philos->data->write);
	}
}
