/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:33:22 by cwick             #+#    #+#             */
/*   Updated: 2024/06/01 13:47:16 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	check_input(int argc, char **argv)
{
	if (check_argc(argc) == 1 || check_argv(argc, argv) == 1)
		return (1);
	return (0);
}

int	check_argc(int argc)
{
	if (argc < 5  || argc > 6)
	{
		printf("%s\n", INPUT_ERR_1);
		return (1);
	}
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
			if (argv[1][0] == '0' || argv[i][j] < '0' || argv[i][j] > '9' || argv[i][j] == '-')
			{
				printf("%s\n", INPUT_ERR_2);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
