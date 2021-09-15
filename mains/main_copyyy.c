/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:48:08 by julian            #+#    #+#             */
/*   Updated: 2021/09/14 17:30:46 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philosophers.h"

/*
** big difference to processes is that threads are sharing memory
** a mutex is sort of a lock around a section of code that protects it from 
** other treads executing it at the same time
** pthread_join() is basically the wait() for threads, so that the main process
** doesn't finish its execution while some threads arent't finished yet
*/

pthread_mutex_t *mutex_fork;
pthread_mutex_t	*mutex_food;

int				nop = 0;
int				ttd = 0;
int				tte = 0;
int				tts = 0;

void	*philosopher(void* arg);
void	grab_fork(int phil, int c);
void	down_forks(int c1, int c2);
int		food_on_table(void);

/*
** nop	- number of philosophers
** ttd	- time to die [ms]
** tte	- time to eat [ms]
** tts	- time toe sleep [ms]
** noms	- number of must eat
*/

int main(int argc, char *argv[])
{
	pthread_t	*philo;
	int			i;
	int			*a;

	if (check_input(argc, argv) != 0)
		return (1);

	// get number of philosophers
	nop = ft_atoi(argv[1]);
	ttd = ft_atoi(argv[2]);
	tte = ft_atoi(argv[3]);
	tts = ft_atoi(argv[4]);
	
	// create mutex for forks
	mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nop);
	if (mutex_fork == NULL)
		return (2);
	i = 0;
	while (++i <= nop)
		if (pthread_mutex_init(&mutex_fork[i], NULL) != 0)
			return(ft_error("Failed to create a mutex\n", 3));

	// create threads aka philosophers
	philo = (pthread_t *)malloc(sizeof(pthread_t) * nop);
	i = 0;
	while (++i <= nop)
	{
		a = (int *)malloc(sizeof(int));
		*a = i;
		if (pthread_create(&philo[i], NULL, &philosopher, a) != 0)
			return(ft_error("Failed to create thread\n", 4));
	}
	
	// join threads aka philosophers
	i = 0;
	while (++i < nop)
	{
		if (pthread_join(philo[i], NULL) != 0)
		{
			printf("Failed to join thread %d\n", i);
			return (3);
		}
		printf("Thread %d has finished execution\n", i);
		
			// return(ft_error("Failed to join thread\n", 5));
	}
	
	// detroy mutex for the forks
	i = 0;
	while (++i <= nop)
		pthread_mutex_destroy(&mutex_fork[i]);
	
	free(mutex_fork);
	free(philo);
	system("leaks philo");
	return (0);
}

void	*philosopher(void* num)
{
	int				id;
	int				left_fork;
	int				right_fork;
	struct timeval	t0;
	struct timeval	t1;
	
	id = *(int*)num;
	right_fork = id;
	left_fork = id + 1;
	if (right_fork == nop)
		left_fork = 1;
	gettimeofday(&t0, NULL);	
	while ((t1.tv_usec - t0.tv_usec) < ttd)
	{
		if (id % 2 == 0)
			usleep(100);
		grab_fork(id, right_fork);
		grab_fork(id, left_fork);
		gettimeofday(&t1, NULL);
		if ((t1.tv_usec - t0.tv_usec) >= ttd)
			break ;
		t0 = t1;
		printf ("%d is eating\n", id);
		usleep(tte);
		down_forks(left_fork, right_fork);
		printf ("%d is sleeping\n", id);
		usleep(tts);
		usleep(tts);
		printf ("%d is thinking\n", id);
		gettimeofday(&t1, NULL);
	}
	printf ("%d died\n", id);
	free(num);
	return (NULL);
}

void	grab_fork(int phil, int c)
{
	pthread_mutex_lock(&mutex_fork[c]);
	printf ("%d has taken a fork %d\n", phil, c);
}

void	down_forks(int c1, int c2)
{
	pthread_mutex_unlock(&mutex_fork[c1]);
	pthread_mutex_unlock(&mutex_fork[c2]);
}
