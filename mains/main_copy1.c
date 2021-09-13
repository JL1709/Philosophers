/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:48:08 by julian            #+#    #+#             */
/*   Updated: 2021/09/13 08:19:57 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philosophers.h"

void *roll_dice(void)
{
	srand(time(NULL));
	int value = (rand() % 6) + 1;
	int	*result = malloc(sizeof(int));
	*result = value;
	// printf("%d\n", value);
	printf("Thread result: %p\n", result);
	return (void *)result;
}

/*
** big difference to processes is that threads are sharing memory
** a mutex is sort of a lock around a section of code that protects it from 
** other treads executing it at the same time
** pthread_join() is basically the wait() for threads
*/

int main(int argc, char *argv[])
{
	int			*res;
	pthread_t	th;

	(void)	argc;
	(void) **argv;
	if (pthread_create(&th, NULL, (void *)roll_dice, NULL) != 0)
		return (1);
	if (pthread_join(th, (void **) &res) != 0)
		return (2);
	printf("Main res: %p\n", res);
	printf("Result: %d\n", *res);
	free(res);
	return (0);
}