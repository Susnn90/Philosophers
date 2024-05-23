/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:26:43 by cwick             #+#    #+#             */
/*   Updated: 2024/05/20 16:35:43 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_data(t_data *table, int argc, char **argv)
{
	table->philo_num = ft_atoi(argv[1]);
	table->death_time = ft_atoi(argv[2]) * 1e3;
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
	table->fninished = 0;
	if (table->philo_num < 1 || table->death_time < 1
		|| table->eat_time < 1 || table->sleep_time < 1)
		error_exit(INIT_ERR_1);
	return (0);
}

void	data_init(t_data *table)
{
	int	i;

	i = 0;
	table->end_simulation = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_num);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_num);
	pthread_mutex_init(&table->table_mutex, NULL);
	while (i < table->philo_num)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].fork_id = i;
		i++;
	}
}

void	philo_init(t_data *table)
{
	int	i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_num)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meal_count = 0;
		pthread_mutex_init(&philo->mutex, NULL);
		philo->data = table;
		assign_forks(philo, table->forks, i);
		i++;
	}
}

void	assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	philo_nbr;

	//even(left,right) / odd(right,left)
	philo_nbr = philo->data->philo_num;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % philo_nbr];
	}
	else
	{
		philo->first_fork = &forks[(philo_pos + 1) % philo_nbr];
		philo->second_fork = &forks[philo_pos];
	}
	printf("PH %d fork: %d\nPH %d fork: %d\n",philo->id, philo->first_fork->fork_id, philo->id, philo->second_fork->fork_id);
}
