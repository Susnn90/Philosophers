/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:13:38 by cwick             #+#    #+#             */
/*   Updated: 2024/05/24 13:16:24 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dinner_start(t_data *table)
{
	int	i;

	i = 0;
	if (table->meals_nbr == 0)
		return ;
	else if (table->philo_num == 0)
	{

	}
	else
	{
		while (i < table->philo_num)
		{
			pthread_create(table->philos[i].tid, NULL, dinner_simulation, table);
			i++;
		}
	}

}
void	*dinner_simulation(void *data)
{
	t_data	*table;

	table = (t_data *)data;

	// t_philo	*philo;

	// philo = (t_philo *)table;
	// wait_all_threads();

	printf("%ld\n", table->meals_nbr);

	return (NULL);
}
