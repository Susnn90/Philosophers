/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:26:43 by cwick             #+#    #+#             */
/*   Updated: 2024/05/24 16:23:32 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_data(t_data *table, int argc, char **argv)
{
	table->philo_num = ft_atoi(argv[1]);
	table->death_time = ft_atoi(argv[2]) * 1e3; //convert to microsec -> 1 x 10^3 == 1000
	table->eat_time = ft_atoi(argv[3]) * 1e3;
	table->sleep_time = ft_atoi(argv[4]) * 1e3;
	table->start_time = 0;
	table->end_simulation = false;
	table->all_threads_ready = false;
	if (argc == 6)
		table->meals_nbr = ft_atoi(argv[5]);
	else
		table->meals_nbr = -1;
	table->dead = 0;
	table->finished = 0;
	if (table->philo_num < 1 || table->death_time < 1
		|| table->eat_time < 1 || table->sleep_time < 1)
		error_exit(INIT_ERR_1);
	return (0);
}

void	data_init(t_data *table)
{
	int		i;

	i = 0;
	table->end_simulation = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_num);
	table->fork = safe_malloc(sizeof(t_fork) * table->philo_num);
	pthread_mutex_init(&table->table_mutex, NULL);
	while (i < table->philo_num)
	{
		pthread_mutex_init(&table->fork[i].fork, NULL);
		table->fork[i].fork_id = i;
		i++;
	}
}

void	philo_init(t_data *table)
{
	int		i;
	// t_philo	*philo;

	i = 0;
	while (i < table->philo_num)
	{
		table->philos[i].id = i + 1;
		table->philos[i].full = false;
		table->philos[i].meal_count = 0;
		pthread_mutex_init(&table->philos[i].mutex, NULL);
		table->philos[i].data = table;
		assign_forks(table, i);
		i++;
	}
}

void	assign_forks(t_data	*table, int philo_pos)
{
	int		philo_nbr;
	t_philo	*philo;

	//even(left,right) / odd(right,left)
	philo_nbr = table->philo_num;
	philo = &table->philos[philo_pos];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &table->fork[philo_pos];
		philo->second_fork = &table->fork[(philo_pos + 1) % philo_nbr];
	}
	else
	{
		philo->first_fork = &table->fork[(philo_pos + 1) % philo_nbr];
		philo->second_fork = &table->fork[philo_pos];
	}
	printf("PH %d fork: %ld\nPH %d fork: %ld\n", philo_pos, philo->first_fork->fork_id, philo_pos, philo->second_fork->fork_id);
}
