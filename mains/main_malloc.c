/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:48:08 by julian            #+#    #+#             */
/*   Updated: 2021/09/14 11:12:42 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philosophers.h"

#define DELAY 5000
#define FOOD 50

void	*philosopher(void *id);
void	grab_fork(int phil, int c);
void	down_forks(int c1, int c2);
int		food_on_table(void);

int				sleep_seconds = 0;
int				nop = 0;
pthread_mutex_t	*mutex_fork;
pthread_mutex_t	*mutex_food;

/*
** nop	- number of philosophers
** ttd	- time to die [ms]
** tte	- time to eat [ms]
** tts	- time toe sleep [ms]
** noms	- number of must eat
*/

int main(int argc, char *argv[])
{
	int				i;
	int				nop;
	pthread_t		*philo;

	// Check Input
	// if (check_input(argc, argv) != 0)
	// 	return (1);

	if (argc == 3)
		sleep_seconds = ft_atoi(argv[2]);

	printf("test0");

	// get number of philosophers
	nop = ft_atoi(argv[1]);

	// create mutex for food
	i = 0;
	mutex_food = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (mutex_food == NULL)
		return (2);
	if (pthread_mutex_init(mutex_food, NULL) != 0)
		return(ft_error("Failed to create a mutex\n", 3));

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
	if (philo == NULL)
		return (2);
	i = 0;
	while (++i <= nop)
		if (pthread_create(&philo[i], NULL, philosopher, (void *)&i) != 0)
			return(ft_error("Failed to create thread\n", 4));
	
	// join threads aka philosophers
	i = 0;
	while (++i <= nop)
		if (pthread_join(philo[i], NULL) != 0)
			return(ft_error("Failed to join thread\n", 5));

	// destroy mutex for food
	pthread_mutex_destroy(mutex_food);
	
	// detroy mutex for the forks
	i = 0;
	while (++i <= nop)
		pthread_mutex_destroy(&mutex_fork[i]);

	// free stuff
	free(mutex_food);
	free(mutex_fork);
	free(philo);
	system("leaks philo");
	return (0);
}

void *philosopher(void *num)
{
	int	id; 
	int	left_fork, right_fork, f;

	id = *(int*)num;
	//printf ("Philosopher %d is done thinking and now ready to eat.\n", id);
	right_fork = id;
	left_fork = id + 1;
	if (left_fork == nop)
		left_fork = 0;
	while ((f = food_on_table()))
	{
		if (id == 1)
			sleep(sleep_seconds);
		grab_fork(id, right_fork);
		grab_fork(id, left_fork);
		printf ("%d is eating\n", id);
		usleep (DELAY * (FOOD - f + 1));
		down_forks(left_fork, right_fork);
	}
	printf ("Philosopher %d is done eating.\n", id);
	return (NULL);
}

int	food_on_table(void)
{
	static int	food = FOOD;
	int myfood;

	pthread_mutex_lock(mutex_food);
	if (food > 0)
		food--;
	myfood = food;
	pthread_mutex_unlock(mutex_food);
	return (myfood);
}

void	grab_fork(int phil, int c)
{
	pthread_mutex_lock(&mutex_fork[c]);
	printf ("%d has taken a fork\n", phil);
}

void	down_forks(int c1, int c2)
{
	pthread_mutex_unlock(&mutex_fork[c1]);
	pthread_mutex_unlock(&mutex_fork[c2]);
}