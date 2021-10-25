/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutex_and_threads.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 13:46:34 by julian            #+#    #+#             */
/*   Updated: 2021/10/25 13:49:22 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	create_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&(data->mutex_printing), NULL) != 0)
			return(printf("Failed to create mutex_print\n"));
	if (pthread_mutex_init(&(data->mutex_death), NULL) != 0)
			return(printf("Failed to create mutex_death\n"));
	if (pthread_mutex_init(&(data->mutex_time), NULL) != 0)
			return(printf("Failed to create mutex_time\n"));
	i = -1;
	while (++i <= data->nop)
		if (pthread_mutex_init(&(data->mutex_fork[i]), NULL) != 0)
			return(printf("Failed to create mutex_fork[%d]\n", i));
	return (0);
}

int	create_run_threads(t_data *data)
{
	int			i;
	t_philo		*philo;
	pthread_t	*thread;
	
	if (!(philo = (t_philo *)malloc(sizeof(t_philo) * data->nop)))
		return (1);
	if (!(thread = (pthread_t *)malloc(sizeof(pthread_t) * data->nop)))
		return (1);
	i = -1;
	while (++i < data->nop)
	{
		init_philosophers(data, philo, i);
		if (pthread_create(&thread[i], NULL, run_philosopher, &philo[i]) != 0)
			return(printf("Failed to create thread\n"));
	}
	i = -1;
	while (++i < data->nop)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (printf("Failed to join thread %d\n", i));
		//printf("Thread %d has finished execution\n", i);
		pthread_mutex_destroy(&(data->mutex_fork[i]));
	}
	pthread_mutex_destroy(&(data->mutex_printing));
	pthread_mutex_destroy(&(data->mutex_death));
	pthread_mutex_destroy(&(data->mutex_time));
	free(philo);
	free(thread);
	return (0);
}