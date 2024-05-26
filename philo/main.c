/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:18:49 by cwick             #+#    #+#             */
/*   Updated: 2024/05/26 12:47:26 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	main (int argc, char **argv)
{
	t_data	table;

	check_input(argc, argv);
	if (parse_data(&table, argc, argv) != 0)
		error_exit(INIT_ERR_2);
	data_init(&table);
	if (table.philo_num == 1)
		return (case_one(&table));
	philo_init(&table);
	// create_thread(argv);
	//init structs
	//thread action
	//Supervisor
	//Monitor
	//detroy Mutexes
	//clear Memory
	ft_exit(&table);
	return (0);
}

void	clear_data(t_data *table)
{
	// if (table->philos)
	// 	free(table->philos->tid);
	if (table->fork)
		free(table->fork);
	if (table->philos)
		free(table->philos);
}
int	case_one(t_data *table)
{
	table->start_time = get_time();
	if (pthread_create(&table->tid[0], NULL, &routine, &table->philos[0]))
		return (error_exit(TH_ERR));
	if (pthread_detach(table->tid[0]) != 0)
		error_exit(DET_ERR);
	while (table->dead == 0)
		ft_usleep(0, table);
	ft_exit(table);
	return (0);
}
