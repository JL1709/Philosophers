/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 13:50:02 by julian            #+#    #+#             */
/*   Updated: 2021/10/25 14:14:10 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	handle_norm(t_data *data, t_philo *philo)
{
	if (data->died == 1)
		return (0);
	if (philo->eat_count > 0)
		philo->eat_count--;
	if (philo->eat_count == 0)
		return (0);
	return (1);
}

static void	init_philo(t_philo *philo)
{
	philo->start_time = get_time();
	philo->last_meal = philo->start_time;
}

void	*run_philosopher(void *arg)
{
	t_philo		*philo;
	t_data		*data;
	pthread_t	death;

	philo = (t_philo *)arg;
	data = philo->data;
	init_philo(philo);
	pthread_create(&death, NULL, death_checker, philo);
	if (philo->id % 2 == 0)
		usleep(10000);
	while (philo->eat_count)
	{
		if (data->died == 1)
			break ;
		eating(data, philo);
		if (!handle_norm(data, philo))
			break ;
		printing(data, philo, "is sleeping\n");
		optimized_sleep(data->tts);
		if (data->died == 1)
			break ;
		printing(data, philo, "is thinking\n");
	}
	pthread_join(death, NULL);
	return (NULL);
}
