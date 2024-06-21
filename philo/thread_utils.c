/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:09:35 by cwick             #+#    #+#             */
/*   Updated: 2024/06/21 18:42:14 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_loop(t_philo *philo)
{
	while (philo->data->dead == 0 && !philo->data->philos_finished_meals)
	{
		eat(philo);
		pthread_mutex_lock(&philo->philo_mutex);
		if (philo->data->dead == 0 && !philo->data->philos_finished_meals)
		{
			messages(SLEEPING, (void *)philo);
			ft_usleep(philo->data->sleep_time);
		}
		pthread_mutex_lock(&philo->data->table_mutex);
		if (philo->data->meals_nbr > 0
			&& philo->meal_count >= philo->data->meals_nbr)
		{
			philo->data->finished++;
			if (philo->data->finished >= philo->data->philo_num)
				philo->data->philos_finished_meals = true;
		}
		pthread_mutex_unlock(&philo->data->table_mutex);
		if (philo->data->dead == 0 && !philo->data->philos_finished_meals)
			messages(THINKING, philo);
		pthread_mutex_unlock(&philo->philo_mutex);
	}
}
