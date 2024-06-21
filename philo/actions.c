/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:13:38 by cwick             #+#    #+#             */
/*   Updated: 2024/06/21 19:11:11 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	messages(char *str, void *philo)
{
	long	time;
	t_philo	*philos;

	philos = (t_philo *)philo;
	if (ft_strcmp(DIED, str) == 0 && philos->data->dead == 0)
	{
		pthread_mutex_lock(&philos->data->table_mutex);
		time = get_time() - philos->data->start_time;
		pthread_mutex_lock(&philos->data->write);
		printf("%s%ld %ld %s%s\n", RED, time, philos->id, str, RST);
		pthread_mutex_unlock(&philos->data->write);
		philos->data->dead = 1;
		pthread_mutex_unlock(&philos->data->table_mutex);
	}
	print_action(str, philos, time);
}

/* return milliseconds */
long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error_exit(TIME_ERR, NULL));
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->first_fork->fork_mutex);
		messages(TAKE_FORKS, (void *)philo);
		pthread_mutex_lock(&philo->second_fork->fork_mutex);
		messages(TAKE_FORKS, (void *)philo);
	}
	else
	{
		pthread_mutex_lock(&philo->second_fork->fork_mutex);
		messages(TAKE_FORKS, (void *)philo);
		pthread_mutex_lock(&philo->first_fork->fork_mutex);
		messages(TAKE_FORKS, (void *)philo);
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->first_fork->fork_mutex);
	pthread_mutex_unlock(&philo->second_fork->fork_mutex);
}

void	eat(t_philo *philo)
{
	if (philo->data->dead == 0 && !philo->data->philos_finished_meals)
	{
		take_forks(philo);
		pthread_mutex_lock(&philo->philo_mutex);
		philo->eating = 1;
		philo->time_to_die = get_time() + philo->data->death_time;
		// pthread_mutex_unlock(&philo->philo_mutex);
		messages(EATING, (void *)philo);
		ft_usleep(philo->data->eat_time);
		// pthread_mutex_lock(&philo->philo_mutex);
		philo->meal_count++;
		philo->eating = 0;
		pthread_mutex_unlock(&philo->philo_mutex);
		drop_forks(philo);
	}
}
