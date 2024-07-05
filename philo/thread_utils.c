/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:09:35 by cwick             #+#    #+#             */
/*   Updated: 2024/07/05 14:53:52 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_loop(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (philo->data->dead == 0 && !philo->data->philos_finished_meals)
	{
		eat(philo);
		pthread_mutex_lock(&philo->data->table_mutex);
		if (philo->meal_count == philo->data->meals_nbr)
			philo->data->finish_count++;
		pthread_mutex_unlock(&philo->data->table_mutex);
		messages(SLEEPING, (void *)philo);
		ft_usleep(philo->data->sleep_time);
		messages(THINKING, philo);
		ft_usleep(1);
	}
}

void	destroy_mutex(t_data *table)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&table->table_mutex);
	while (++i < table->philo_num)
		pthread_mutex_destroy(&table->fork[i].fork_mutex);
	pthread_mutex_unlock(&table->table_mutex);
	i = -1;
	pthread_mutex_lock(&table->table_mutex);
	while (++i < table->philo_num)
		pthread_mutex_destroy(&table->philos[i].philo_mutex);
	pthread_mutex_unlock(&table->table_mutex);
	pthread_mutex_destroy(&table->write);
	pthread_mutex_destroy(&table->start_mutex);
	pthread_mutex_destroy(&table->table_mutex);
}
