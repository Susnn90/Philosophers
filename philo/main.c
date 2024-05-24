/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:18:49 by cwick             #+#    #+#             */
/*   Updated: 2024/05/24 15:58:23 by cwick            ###   ########.fr       */
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

void	exit_point(void)
{
	t_data	table;

	pthread_mutex_destroy(&table.table_mutex);
	exit (EXIT_FAILURE);
}
