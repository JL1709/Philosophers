/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:48:08 by julian            #+#    #+#             */
/*   Updated: 2021/09/14 14:31:42 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philosophers.h"


int main(void)
{
	struct timeval	t0;
	struct timeval	t1;

	gettimeofday(&t0, NULL);
	while ((t1.tv_usec - t0.tv_usec) < 200)
	{
		gettimeofday(&t1, NULL);
		printf("%d\n", t1.tv_usec - t0.tv_usec);
	}	
	return (0);
}
