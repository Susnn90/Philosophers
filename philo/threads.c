/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:10:25 by cwick             #+#    #+#             */
/*   Updated: 2024/05/26 17:13:56 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*routine(void *philo_ptr)
{
	t_philo	*philo;
	// t_data	*table;

	philo = (t_philo *)philo_ptr;
	philo->time_to_die = philo->data->death_time + get_time();
	if (pthread_create(&philo->t1, NULL, &supervisor, (void *)philo))
		return ((void *)1);
	while (philo->data->dead == 0)
	{
		// eat(philo);
		messages(THINKING, philo);
	}
	if (pthread_join(philo->t1, NULL))
		return ((void *)1);
	return ((void *)0);
}

void	*supervisor(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->philo_mutex);
		if (get_time() >= philo->time_to_die && philo->eating == 0)
			messages(DIED, philo);
		if (philo->meal_count == philo->data->meals_nbr)
		{
			pthread_mutex_lock(&philo->data->table_mutex);
			philo->data->finished++;
			philo->meal_count++;
			pthread_mutex_unlock(&philo->data->table_mutex);
		}
		pthread_mutex_unlock(&philo->philo_mutex);
	}
	return ((void *)0);
}

void	*monitor(void *data_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)data_ptr;
	pthread_mutex_lock(&philo->data->write);
	printf("data val: %ld", philo->data->dead);
	pthread_mutex_unlock(&philo->data->write);
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->philo_mutex);
		if (philo->data->finished >= philo->data->philo_num)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->philo_mutex);
	}
	return ((void *)0);
}

int	thread_init(t_data *table)
{
	int			i;
	pthread_t	t0;

	i = 0;
	table->start_time = get_time();
	if (table->meals_nbr > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, &table->philos[0]))
			return (error_exit(TH_ERR, table));
		pthread_detach(t0);
	}
	while (i++ < table->philo_num)
	{
		if (pthread_create(&table->tid[i], NULL, &routine, &table->philos[i]))
			return (error_exit(TH_ERR, table));
		ft_usleep(1);
	}
	i = 0;
	while (i++ < table->philo_num)
	{
		if (pthread_join(table->tid[i], NULL))
			return (error_exit(JOIN_ERR, table));
	}
	return (0);
}
