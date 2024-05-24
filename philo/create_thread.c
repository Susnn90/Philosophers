/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:10:25 by cwick             #+#    #+#             */
/*   Updated: 2024/05/24 17:00:48 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*table;

	philo = (t_philo *)arg;
	while (!table->end_simulation)
	{
		//logic for forks
		pthread_mutex_lock(&table->table_mutex);
		pthread_mutex_lock(&philo->philo_mutex);
		if (pthread_mutex_trylock(&philo->first_fork->fork) == 0)
		{
			if (pthread_mutex_trylock(&philo->second_fork->fork) == 0)
			{
				philo->status = TAKE_FORKS;
				printf("has taken a fork\n");
			}
		}
		pthread_mutex_unlock(&table->table_mutex);
		pthread_mutex_unlock(&philo->philo_mutex);
		//logic for eating
		//logic for sleeping
		//logic for thinking
	}
	return (NULL);
}

int	run_simulation(t_data *table)
{
	int			i;

	i = 0;
	// Create threads for each philosopher
	while (i < table->philo_num)
	{
		if (pthread_create(table->philos[i].tid, NULL, &philo_routine, &table->philos[i]) != 0)
			error_exit(TH_ERR);
		i++;
	}
	i = 0;
	// Join threads
	while (i < table->philo_num)
	{
		if (pthread_join(&table->philos[i].tid, NULL) != 0)
			error_exit(JOIN_ERR);
		i++;
	}
	return (0);
}
