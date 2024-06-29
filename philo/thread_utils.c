/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:09:35 by cwick             #+#    #+#             */
/*   Updated: 2024/06/29 13:00:17 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_loop(t_philo *philo)
{
	while (philo->data->dead == 0 && !philo->data->philos_finished_meals)
	{
		eat(philo);
		pthread_mutex_lock(&philo->data->table_mutex);
		if (philo->meal_count == philo->data->meals_nbr)
			philo->data->finish_count++;
		pthread_mutex_unlock(&philo->data->table_mutex);
		messages(SLEEPING, (void *)philo);
		pthread_mutex_lock(&philo->philo_mutex);
		if (philo->data->dead == 0 && !philo->data->philos_finished_meals)
			ft_usleep(philo->data->sleep_time);
		pthread_mutex_unlock(&philo->philo_mutex);
		messages(THINKING, philo);
		ft_usleep(1);
	}
}
