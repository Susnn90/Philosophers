/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:09:35 by cwick             #+#    #+#             */
/*   Updated: 2024/06/22 16:41:39 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_loop(t_philo *philo)
{
	while (philo->data->dead == 0 && !philo->data->philos_finished_meals)
	{
		if (philo->id % 2 != 0)
			ft_usleep(1);
		eat(philo);
		if (philo->data->dead == 0 && !philo->data->philos_finished_meals)
		{
			messages(SLEEPING, (void *)philo);
			ft_usleep(philo->data->sleep_time);
		}
		pthread_mutex_lock(&philo->data->table_mutex);
		if (philo->meal_count >= philo->data->meals_nbr)
			philo->data->finished++;
		if (philo->data->finished >= philo->data->philo_num)
			philo->data->philos_finished_meals = true;
		pthread_mutex_unlock(&philo->data->table_mutex);
		if (philo->data->dead == 0 && !philo->data->philos_finished_meals)
			messages(THINKING, philo);
	}
}
