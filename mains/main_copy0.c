/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:48:08 by julian            #+#    #+#             */
/*   Updated: 2021/09/13 09:22:29 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philosophers.h"
#include <stdlib.h>

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

/*
** big difference to processes is that threads are sharing memory
** a mutex is sort of a lock around a section of code that protects it from 
** other treads executing it at the same time
** pthread_join() is basically the wait() for threads
*/

void *routine(void)
{
	sleep(1);
	printf("Finished Execution\n");
	return (NULL);
}

int main(int argc, char *argv[])
{
	pthread_t		th[2];
	pthread_attr_t	detachedThread;
	
	(void)	argc;
	(void) **argv;
	pthread_attr_init(&detachedThread);
	pthread_attr_setdetachstate(&detachedThread, PTHREAD_CREATE_DETACHED);
	for (int i = 0; i < 2; i++)
	{
		if (pthread_create(&th[i], &detachedThread, (void *)&routine, NULL) != 0)
		{
			perror("Failed to create thread\n");
			return (1);
		}
		// pthread_detach(th[i]) --> also possible
	}
	pthread_attr_destroy(&detachedThread);
	pthread_exit(0);
}