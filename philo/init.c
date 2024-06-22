/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:26:43 by cwick             #+#    #+#             */
/*   Updated: 2024/06/22 14:49:27 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc(t_data *table)
{
	table->philos = malloc(sizeof(t_philo) * table->philo_num);
	if (!table->philos)
		return (error_exit(ALLOC_ERR_3, table));
	table->fork = malloc(sizeof(t_fork) * table->philo_num);
	if (!table->fork)
	{
		free (table->philos);
		return (error_exit(ALLOC_ERR_2, table));
	}
	table->tid = malloc(sizeof(pthread_t) * table->philo_num);
	if (!table->tid)
	{
		free(table->philos);
		free(table->fork);
		return (error_exit(ALLOC_ERR_1, table));
	}
	return (0);
}

int	data_init(t_data *table, int argc, char **argv)
{
	table->philo_num = ft_atoi(argv[1]);
	table->death_time = ft_atoi(argv[2]);
	table->eat_time = ft_atoi(argv[3]);
	table->sleep_time = ft_atoi(argv[4]);
	table->start_time = 0;
	table->dead = 0;
	table->finished = 0;
	table->philos_finished_meals = false;
	if (argc == 6)
		table->meals_nbr = ft_atoi(argv[5]);
	else
		table->meals_nbr = -1;
	if (table->philo_num < 1 || table->death_time < 1
		|| table->eat_time < 1 || table->sleep_time < 1)
		error_exit(INIT_ERR_1, table);
	if (pthread_mutex_init(&table->write, NULL) != 0)
		error_exit(MUTEX_ERR, table);
	if (pthread_mutex_init(&table->table_mutex, NULL) != 0)
		error_exit(MUTEX_ERR, table);
	if (pthread_mutex_init(&table->start_mutex, NULL) != 0)
		error_exit(MUTEX_ERR, table);
	return (0);
}

int	philo_init(t_data *table)
{
	int		i;

	i = -1;
	while (++i < table->philo_num)
	{
		table->philos[i].data = table;
		table->philos[i].id = i + 1;
		table->philos[i].time_to_die = table->death_time;
		table->philos[i].meal_count = 0;
		table->philos[i].eating = 0;
		if (pthread_mutex_init(&table->philos[i].philo_mutex, NULL) != 0)
			error_exit(MUTEX_ERR, table);
	}
	return (0);
}

int	fork_init(t_data *table)
{
	int		i;

	i = -1;
	while (++i < table->philo_num)
	{
		if (pthread_mutex_init(&table->fork[i].fork_mutex, NULL) != 0)
			error_exit(MUTEX_ERR, table);
	}
	i = 0;
	pthread_mutex_lock(&table->philos->philo_mutex);
	table->philos[0].first_fork = &table->fork[i];
	table->philos[0].second_fork = &table->fork[table->philo_num - 1];
	while (++i < table->philo_num)
	{
		table->philos[i].first_fork = &table->fork[i - 1];
		table->philos[i].second_fork = &table->fork[i];
	}
	pthread_mutex_unlock(&table->philos->philo_mutex);
	return (0);
}

int	init(t_data *table, int argc, char **argv)
{
	if (data_init(table, argc, argv))
		return (1);
	if (alloc(table))
		return (1);
	if (philo_init(table))
		return (1);
	if (fork_init(table))
		return (1);
	return (0);
}


		// // pthread_mutex_lock(&table->philos->philo_mutex);
		// if (table->philos[i].id % 2 == 0)
		// {
		// 	table->philos[i].first_fork = &table->fork[i  - 1];
		// 	table->philos[i].second_fork = &table->fork[i];
		// }
		// else
		// {
		// 	table->philos[i].first_fork = &table->fork[i];
		// 	table->philos[i].second_fork = &table->fork[i - 1];
		// }
		// // pthread_mutex_unlock(&table->philos->philo_mutex);