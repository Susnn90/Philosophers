/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:18:49 by cwick             #+#    #+#             */
/*   Updated: 2024/05/20 16:41:04 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	main (int argc, char **argv)
{
	t_data	table;

	//check input
	check_input(argc, argv);
	parse_data(&table, argc, argv);
	data_init(&table);
	philo_init(&table);
	// create_thread(argv);
	//init structs
	//thread action
	//Supervisor
	//Monitor
	//detroy Mutexes
	//clear Memory
	return (0);
}

void	exit_point()
{
	t_data	table;

	pthread_mutex_destroy(&table.table_mutex);
	exit (EXIT_FAILURE);
}
