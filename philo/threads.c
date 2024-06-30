/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:10:25 by cwick             #+#    #+#             */
/*   Updated: 2024/06/30 16:24:19 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	pthread_mutex_lock(&philo->data->start_mutex);
	pthread_mutex_unlock(&philo->data->start_mutex);
	if (pthread_create(&philo->t_supervisor, NULL, &supervisor, (void *)philo))
		return ((void *)1);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->time_to_die = philo->data->death_time + get_time();
	pthread_mutex_unlock(&philo->philo_mutex);
	routine_loop(philo);
	if (pthread_join(philo->t_supervisor, NULL) != 0)
		return ((void *)1);
	return ((void *)0);
}

void	*supervisor(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	while (philo->data->dead == 0 && !philo->data->philos_finished_meals)
	{
		pthread_mutex_lock(&philo->philo_mutex);
		if (get_time() > philo->time_to_die && philo->eating == 0)
		{
			messages(DIED, philo);
			pthread_mutex_lock(&philo->data->table_mutex);
			philo->data->dead = 1;
			pthread_mutex_unlock(&philo->data->table_mutex);
		}
		pthread_mutex_unlock(&philo->philo_mutex);
	}
	return ((void *)0);
}

void	*monitor(void *data_ptr)
{
	t_data	*table;

	table = (t_data *)data_ptr;
	while (table->dead == 0 && !table->philos_finished_meals)
	{
		pthread_mutex_lock(&table->table_mutex);
		if (table->finish_count == table->philo_num)
			table->philos_finished_meals = true;
		pthread_mutex_unlock(&table->table_mutex);
	}
	return ((void *)0);
}

int	thread_init(t_data *table)
{
	int			i;

	i = -1;
	table->start_time = get_time();
	if (table->meals_nbr >= 0)
	{
		if (pthread_create(&table->philos->t_monitor,
				NULL, &monitor, table) != 0)
			return (error_exit(TH_ERR, table));
	}
	pthread_mutex_lock(&table->start_mutex);
	while (++i < table->philo_num)
	{
		if (pthread_create(&table->tid[i],
				NULL, &routine, &table->philos[i]) != 0)
			return (error_exit(TH_ERR, table));
	}
	pthread_mutex_unlock(&table->start_mutex);
	thread_join(table);
	return (0);
}

int	thread_join(t_data *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_num)
	{
		if (pthread_join(table->tid[i], NULL) != 0)
			return (error_exit(JOIN_ERR, table));
		ft_usleep(10);
	}
	if (table->meals_nbr > 0)
	{
		if (pthread_join(table->philos->t_monitor, NULL) != 0)
			return (error_exit(JOIN_ERR, table));
	}
	return (0);
}
