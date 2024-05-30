/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:10:25 by cwick             #+#    #+#             */
/*   Updated: 2024/05/30 18:39:41 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	philo->time_to_die = philo->data->death_time + get_time();
	if (pthread_create(&philo->t1, NULL, &supervisor, (void *)philo))
		return ((void *)1);
	while (philo->data->dead == 0)
	{
		eat(philo);
		messages(THINKING, philo);
	}
	if (pthread_join(philo->t1, NULL))
		return ((void *)1);
	return ((void *)0);
}

void	*supervisor(void *philo_ptr)
{
	t_philo	*philo;
	t_data	*table;

	philo = (t_philo *) philo_ptr;
	table = philo->data;
	while (table->dead == 0)
	{
		pthread_mutex_lock(&philo->philo_mutex);
		if (get_time() > philo->time_to_die && philo->eating == 0)
		{
			pthread_mutex_lock(&table->write);
			messages(DIED, philo);
			// error_exit("Simulation ends\n", table);
			pthread_mutex_unlock(&table->write);
			table->dead = 1;
		}
		if (philo->meal_count >= table->meals_nbr)
		{
			pthread_mutex_lock(&table->table_mutex);
			table->finished++;
			// philo->meal_count++;
			pthread_mutex_unlock(&table->table_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->philo_mutex);
	}
	return ((void *)0);
}

void	*monitor(void *data_ptr)
{
	t_data	*table;

	table = (t_data *)data_ptr;
	while (table->dead == 0)
	{
		pthread_mutex_lock(&table->table_mutex);
		if (table->finished >= table->philo_num)
				table->dead = 1;
		pthread_mutex_unlock(&table->table_mutex);
		ft_usleep(1);
	}
	return (NULL);
}

int	thread_init(t_data *table)
{
	int			i;
	pthread_t	t0;

	i = -1;
	table->start_time = get_time();
	if (table->meals_nbr > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, &table->philos[0]))
			return (error_exit(TH_ERR, table));
	}
	while (++i < table->philo_num)
	{
		if (pthread_create(&table->tid[i], NULL, &routine, &table->philos[i]))
			return (error_exit(TH_ERR, table));
		// ft_usleep(1);
	}
	i = -1;
	while (++i < table->philo_num)
	{
		if (pthread_join(table->tid[i], NULL))
			return (error_exit(JOIN_ERR, table));
	}
	return (0);
}
