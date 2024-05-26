/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:46:01 by cwick             #+#    #+#             */
/*   Updated: 2024/05/26 13:38:42 by cwick            ###   ########.fr       */
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
void	error_exit(const char *error, t_data *table)
{
	printf("%s\n", error);
	if (table)
		ft_exit (table);
	return (1);
}
void	ft_exit(t_data *table)
{
	int	i;

	i = 0;
	while (i++ < table->philo_num)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].philo_mutex);
	}
	pthread_mutex_destroy(&table->write);
	// pthread_mutex_destroy(&table->lock);
	clear_data(table);
}

int	ft_usleep(__useconds_t time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}
