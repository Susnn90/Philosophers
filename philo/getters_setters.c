/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:41:31 by cwick             #+#    #+#             */
/*   Updated: 2024/05/20 16:58:44 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(&mutex);
	*dest = value;
	pthread_mutex_unlock(&mutex);
}
bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	ret;

	pthread_mutex_lock(&mutex);
	ret = *value;
	pthread_mutex_unlock(&mutex);
	return (ret);
}
void	set_long(pthread_mutex_t *mutex,long *dest, long value)
{
	pthread_mutex_lock(&mutex);
	*dest = value;
	pthread_mutex_unlock(&mutex);
}
long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	ret;

	pthread_mutex_lock(&mutex);
	ret = *value;
	pthread_mutex_unlock(&mutex);
	return (ret);
}
bool	simulation_finished(t_data *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
