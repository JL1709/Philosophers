/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:48:08 by julian            #+#    #+#             */
/*   Updated: 2021/09/14 12:39:10 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philosophers.h"


int main(void)
{
	struct timeval	t0;
	struct timeval	t1;
	long			elapsed;

	gettimeofday(&t0, NULL);
	printf("seconds : %ld\nmicro seconds : %d\n", t0.tv_sec, t0.tv_usec);
	gettimeofday(&t1, 0);
	// It counts microseconds. Divide by 1000 if you need milliseconds
	elapsed = t1.tv_usec-t0.tv_usec;
	printf("%ld\n", elapsed);
	
	return (0);
}
