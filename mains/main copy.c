/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:48:08 by julian            #+#    #+#             */
/*   Updated: 2021/09/13 09:27:42 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philosophers.h"

int	mails = 0;
pthread_mutex_t mutex;

void routine(void)
{
	for (int i = 0; i < 1000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
		
}

/*
** big difference to processes is that threads are sharing memory
** a mutex is sort of a lock around a section of code that protects it from 
** other treads executing it at the same time
** pthread_join() is basically the wait() for threads
*/

int main(int argc, char *argv[])
{
	pthread_t	th[8];
	int			i;

	(void)	argc;
	(void) **argv;
	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < 8; i++)
	{
		if (pthread_create(&th[i], NULL, (void *)routine, NULL) != 0)
		{
			perror("Failed to create thread\n");
			return (1);
		}
		printf("Thread %d has started\n", i);
	}
	for (i = 0; i < 8; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (3);
		printf("Thread %d has finished execution\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d \n", mails);
	return (0);
}