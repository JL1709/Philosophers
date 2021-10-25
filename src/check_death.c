/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 13:50:36 by julian            #+#    #+#             */
/*   Updated: 2021/10/25 13:50:52 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*death_checker(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;

	pthread_mutex_lock(&data->mutex_time);
	while (get_time() - philo->last_meal <= data->ttd)
	{
		pthread_mutex_unlock(&data->mutex_time);
		usleep(100);
		pthread_mutex_lock(&data->mutex_time);
	}
	pthread_mutex_unlock(&data->mutex_time);
	if (philo->eat_count == 0)
		return (NULL);
	pthread_mutex_lock(&data->mutex_death);
	if (data->died == 1)
	{
		pthread_mutex_unlock(&data->mutex_death);
		return (NULL);
	}
	printing(data, philo, "died\n");
	data->died = 1;
	pthread_mutex_unlock(&data->mutex_death);
	return (NULL);
}
