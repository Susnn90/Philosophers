/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:33:22 by cwick             #+#    #+#             */
/*   Updated: 2024/05/26 14:59:36 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	check_input(int argc, char **argv)
{
	check_argc(argc);
	check_argv(argc, argv);
}

int	check_argc(int argc)
{
	if (argc < 5  || argc > 6)
		error_exit(INPUT_ERR_1, NULL);
	return (0);
}
int	check_argv(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == ' ' || argv[i][j] == '+')
			{
				j++;
				continue;
			}
			if (argv[i][j] < '0' || argv[i][j] > '9' || argv[i][j] == '-')
				error_exit(INPUT_ERR_2, NULL);
			j++;
		}
		i++;
	}
	return (0);
}
