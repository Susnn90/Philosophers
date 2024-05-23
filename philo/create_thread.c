/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:10:25 by cwick             #+#    #+#             */
/*   Updated: 2024/05/20 12:47:00 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	static int	i = 1;
	pthread_mutex_t *mutex;

	mutex = (pthread_mutex_t *)arg;

	pthread_mutex_lock(mutex);
	printf("Hello World from Philo %d\n", i);
	i++;
	pthread_mutex_unlock(mutex);
	return (NULL);
}

int	create_thread(char **argv)
{
	pthread_t	philos[ft_atoi(argv[1])];
	pthread_mutex_t	mutex;
	int			i;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < ft_atoi(argv[1]))
	{
		if (pthread_create(&philos[i], NULL, &routine, &mutex) != 0)
			error_exit(TH_ERR);
		i++;
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		if (pthread_join(philos[i], NULL) != 0)
			error_exit(JOIN_ERR);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}
