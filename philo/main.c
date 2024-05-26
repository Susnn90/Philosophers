/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:18:49 by cwick             #+#    #+#             */
/*   Updated: 2024/05/26 16:45:27 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	main (int argc, char **argv)
{
	t_data	table;

	check_input(argc, argv);
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
	int	i;

	i = 0;
	while (i++ < table->philo_num)
	{
		pthread_mutex_destroy(&table->fork[i].fork_mutex);
		pthread_mutex_destroy(&table->philos[i].philo_mutex);
	}
	pthread_mutex_destroy(&table->write);
	pthread_mutex_destroy(&table->table_mutex);
	clear_data(table);
}

void	clear_data(t_data *table)
{
	if (table->philos)
		free(table->philos);
	if (table->fork)
		free(table->fork);
	if (table->tid)
		free(table->tid);
}
int	case_one(t_data *table)
{
	table->start_time = get_time();
	if (pthread_create(&table->tid[0], NULL, &routine, &table->philos[0]))
		return (error_exit(TH_ERR, table));
	if (pthread_detach(table->tid[0]) != 0)
		error_exit(DET_ERR, table);
	while (table->dead == 0)
		ft_usleep(0);
	ft_exit(table);
	return (0);
}
