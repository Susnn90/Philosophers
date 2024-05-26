/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:13:38 by cwick             #+#    #+#             */
/*   Updated: 2024/05/26 12:13:26 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	messages(char *str, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_time;

}
long	get_time(void)
{
	struct timeval	tv;

	if(gettimeofday(&tv, NULL))
		return (error_exit(TIME_ERR));
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}
