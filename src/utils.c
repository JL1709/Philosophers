/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 09:35:47 by julian            #+#    #+#             */
/*   Updated: 2021/10/25 13:41:47 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	number;

	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	number = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + str[i] - 48;
		i++;
	}
	return (number * sign);
}

void	init_philosophers(t_data *data, t_philo *philo, int i)
{
		philo[i].id = i + 1;
		philo[i].eat_count = data->nome;
		philo[i].last_meal = 0;
		philo[i].data = data;
}

/*
** The timeval structure specifies a time value in 
** seconds (tv_sec [s]) and microseconds (tv_usec [μs])
*/

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	optimized_sleep(int stop_sleeping)
{
	long long	start_sleeping;
	long long	sleep;

	start_sleeping = get_time();
	sleep = 0;
	while (sleep <= stop_sleeping)
	{
		sleep = get_time() - start_sleeping;
		usleep(100);
	}
}

void	printing(t_data *data, t_philo *philo, char *s)
{
	pthread_mutex_lock(&(data->mutex_printing));
	printf("%lld\t", get_time() - philo->start_time);
	printf("%d %s", philo->id, s);
	pthread_mutex_unlock(&(data->mutex_printing));
}
