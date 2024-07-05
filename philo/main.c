/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:18:49 by cwick             #+#    #+#             */
/*   Updated: 2024/07/05 16:10:04 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		table;

	if (check_input(argc, argv) == 1)
		return (1);
	if (init(&table, argc, argv))
		error_exit(INIT_ERR_2, NULL);
	if (table.philo_num == 1)
		return (case_one(&table));
	if (thread_init(&table))
		return (1);
	ft_exit(&table);
	return (0);
}

int	error_exit(char *error, t_data *table)
{
	printf("%s\n", error);
	if (table)
		ft_exit (table);
	return (1);
}

void	ft_exit(t_data *table)
{
	if (!table)
		return ;
	while (1)
	{
		pthread_mutex_lock(&table->table_mutex);
		if (table->philos_finished_meals == true || table->dead == 1)
		{
			pthread_mutex_unlock(&table->table_mutex);
			thread_join(table);
			break ;
		}
		pthread_mutex_unlock(&table->table_mutex);
		ft_usleep(1);
	}
	while (1)
	{
		if (table->philos_finished_meals == true || table->dead == 1)
		{
			destroy_mutex(table);
			break ;
		}
		ft_usleep(1);
	}
	clear_data(table);
}

void	clear_data(t_data *table)
{
	if (!table)
		return ;
	if (table)
	{
		if (table->tid)
			free(table->tid);
		if (table->philos)
			free(table->philos);
		if (table->fork)
			free(table->fork);
	}
}

int	case_one(t_data *table)
{
	table->start_time = get_time();
	if (pthread_create(&table->tid[0], NULL, &routine, &table->philos[0]))
		return (error_exit(TH_ERR, table));
	pthread_detach(table->tid[0]);
	while (1)
	{
		pthread_mutex_lock(&table->table_mutex);
		if (table->dead == 1)
		{
			pthread_mutex_unlock(&table->table_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->table_mutex);
		ft_usleep(10);
	}
	ft_exit(table);
	return (0);
}
