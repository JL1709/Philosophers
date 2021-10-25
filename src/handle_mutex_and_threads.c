/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutex_and_threads.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 13:46:34 by julian            #+#    #+#             */
/*   Updated: 2021/10/25 14:25:11 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	create_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&(data->mutex_printing), NULL) != 0)
		return (printf("Failed to create mutex_print\n"));
	if (pthread_mutex_init(&(data->mutex_death), NULL) != 0)
		return (printf("Failed to create mutex_death\n"));
	if (pthread_mutex_init(&(data->mutex_time), NULL) != 0)
		return (printf("Failed to create mutex_time\n"));
	i = -1;
	while (++i <= data->nop)
		if (pthread_mutex_init(&(data->mutex_fork[i]), NULL) != 0)
			return (printf("Failed to create mutex_fork[%d]\n", i));
	return (0);
}

static int	terminate_threads(t_data *data, pthread_t *thread)
{
	int	i;

	i = -1;
	while (++i < data->nop)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (printf("Failed to join thread %d\n", i));
		pthread_mutex_destroy(&(data->mutex_fork[i]));
	}
	pthread_mutex_destroy(&(data->mutex_printing));
	pthread_mutex_destroy(&(data->mutex_death));
	pthread_mutex_destroy(&(data->mutex_time));
	return (0);
}

int	create_run_threads(t_data *data)
{
	int			i;
	t_philo		*philo;
	pthread_t	*thread;

	philo = (t_philo *)malloc(sizeof(t_philo) * data->nop);
	if (philo == NULL)
		return (1);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * data->nop);
	if (thread == NULL)
		return (1);
	i = -1;
	while (++i < data->nop)
	{
		init_philosophers(data, philo, i);
		if (pthread_create(&thread[i], NULL, run_philosopher, &philo[i]) != 0)
			return (printf("Failed to create thread\n"));
	}
	if (terminate_threads(data, thread) != 0)
		return (1);
	free(philo);
	free(thread);
	return (0);
}
