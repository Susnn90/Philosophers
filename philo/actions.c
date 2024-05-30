/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:13:38 by cwick             #+#    #+#             */
/*   Updated: 2024/05/30 18:45:39 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	messages(char *str, void *philo)
{
	long	time;
	t_philo *philos;
	t_data	*table;

	philos = (t_philo *)philo;
	table = philos->data;
	pthread_mutex_lock(&table->write);
	time = get_time() - table->start_time;
	if (ft_strcmp(DIED, str) == 0 && philos->data->dead == 0)
	{
		printf("%ld %ld %s\n", time, philos->id, str);
		table->dead = 1;
	}
	if (!table->dead)
		printf("%ld %ld %s\n", time, philos->id, str);
	pthread_mutex_unlock(&table->write);
}

long	get_time(void)
{
	struct timeval	tv;

	if(gettimeofday(&tv, NULL))
		return (error_exit(TIME_ERR, NULL));
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork_mutex);
	messages(TAKE_FORKS, (void *)philo);
	pthread_mutex_lock(philo->second_fork_mutex);
	messages(TAKE_FORKS, (void *)philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->first_fork_mutex);
	pthread_mutex_unlock(philo->second_fork_mutex);
	messages(SLEEPING, (void *)philo);
	ft_usleep(philo->data->sleep_time);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->eating = 1;
	philo->time_to_die = get_time() + philo->data->death_time;
	messages(EATING, (void *)philo);
	philo->meal_count++;
	ft_usleep(philo->data->eat_time);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->philo_mutex);
	drop_forks(philo);
}
