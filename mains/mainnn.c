/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main copy2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:48:08 by julian            #+#    #+#             */
/*   Updated: 2021/09/13 16:07:10 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philosophers.h"


pthread_mutex_t mutex_fork;

/*
** big difference to processes is that threads are sharing memory
** a mutex is sort of a lock around a section of code that protects it from 
** other treads executing it at the same time
** pthread_join() is basically the wait() for threads, so that the main process
** doesn't finish its execution while some threads arent't finished yet
*/

void *philosopher(void *arg)
{
	int	index = *(int*)arg;
	int sum = 0;
	for (int j = 0; j < 5; j++)
		sum += primes[index + j];
	printf("Local sum : %d\n", sum);
	*(int*)arg = sum;
	return (arg);
}

/*
** nop	- number of philosophers
** ttd	- time to die [ms]
** tte	- time to eat [ms]
** tts	- time toe sleep [ms]
** noms	- number of must eat
*/

int main(int argc, char *argv[])
{
	pthread_t	*threads;
	int			i;
	int			*a;
	int			nop;

	if (check_input(argc, argv) != 0)
		return (1);
	nop = ft_atoi(argv[1]);
	threads = (pthread_t *)malloc(sizeof(pthread_t) * nop);
	pthread_mutex_init(&mutex_fork, NULL);
	i = 0;
	a = (int *)malloc(sizeof(int) * nop);
	while (++i < nop + 1)
	{
		*a++ = i;
		if (pthread_create(&threads[i], NULL, philosopher, a) != 0)
		{
			perror("Failed to create thread\n");
			return (2);
		}
	}
	i = 0;
	while (++i < nop + 1)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			perror("Failed to join thread\n");
			return (3);
		}
	}
	pthread_mutex_destroy(&mutex_fork);
	free(threads);
	free(a);
	return (0);
}