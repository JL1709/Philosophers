/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_copy2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:48:08 by julian            #+#    #+#             */
/*   Updated: 2021/09/13 15:08:39 by julian           ###   ########.fr       */
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

void *routine(void *arg)
{
	int	index = *(int*)arg;
	int sum = 0;
	for (int j = 0; j < 5; j++)
		sum += primes[index + j];
	printf("Local sum : %d\n", sum);
	*(int*)arg = sum;
	return (arg);
}

int main(int argc, char *argv[])
{
	pthread_t	th[2];
	int			i;

	(void)	argc;
	(void) **argv;
	for (i = 0; i < 2; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
		{
			perror("Failed to create thread\n");
			return (1);
		}
	}
	int globalSum = 0;
	for (i = 0; i < 2; i++)
	{
		int *result;
		if (pthread_join(th[i], (void **) &result) != 0)
			return (3);
		globalSum += *result;
		free(result);
	}
	printf("Global sum: %d\n", globalSum);
	return (0);
}