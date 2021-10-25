/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_eating.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:27:02 by julian            #+#    #+#             */
/*   Updated: 2021/10/25 14:38:13 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	handle_just_one_philo(t_data *data)
{
	while (data->died != 1)
		usleep(100);
	return ;
}

static void	handle_unlock(t_data *data, int *forks, int i)
{
	if (i == 1)
	{
		pthread_mutex_unlock(&(data->mutex_fork[forks[0]]));
		return ;
	}
	else
	{
		pthread_mutex_unlock(&(data->mutex_fork[forks[0]]));
		pthread_mutex_unlock(&(data->mutex_fork[forks[1]]));
		return ;
	}
}

void	eating(t_data *data, t_philo *philo)
{
	int	forks[2];

	forks[0] = philo->id;
	forks[1] = (philo->id + 1) % data->nop;
	pthread_mutex_lock(&(data->mutex_fork[forks[0]]));
	if (data->died == 1)
		return (handle_unlock(data, forks, 1));
	printing(data, philo, "has taken a fork\n");
	if (data->nop == 1)
		return (handle_just_one_philo(data));
	pthread_mutex_lock(&(data->mutex_fork[forks[1]]));
	if (data->died == 1)
		return (handle_unlock(data, forks, 2));
	printing(data, philo, "has taken a fork\n");
	printing(data, philo, "is eating\n");
	pthread_mutex_lock(&data->mutex_time);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&data->mutex_time);
	optimized_sleep(data->tte);
	pthread_mutex_unlock(&(data->mutex_fork[forks[0]]));
	pthread_mutex_unlock(&(data->mutex_fork[forks[1]]));
}
