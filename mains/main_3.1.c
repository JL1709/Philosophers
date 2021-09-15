/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:48:08 by julian            #+#    #+#             */
/*   Updated: 2021/09/14 10:25:12 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philosophers.h"

#define PHILOS 5
#define DELAY 5000
#define FOOD 50

void	*philosopher(void *id);
void	grab_fork(int phil, int c);
void	down_forks(int c1, int c2);
int		food_on_table(void);

pthread_mutex_t	mutex_fork[PHILOS];
pthread_t		philo[PHILOS];
pthread_mutex_t	mutex_food;
int				sleep_seconds = 0;
int				nop = 0;

int main(int argc, char *argv[])
{
	int	i;
	int	*a;

	if (argc == 2)
		sleep_seconds = atoi (argv[1]);
	pthread_mutex_init (&mutex_food, NULL);
	
	for (i = 1; i <= PHILOS; i++)
		pthread_mutex_init (&mutex_fork[i], NULL);
	a = (int *)malloc(sizeof(int) * PHILOS);
	for (i = 1; i <= PHILOS; i++)
	{
		*a++ = i;
		pthread_create (&philo[i], NULL, philosopher, a);
	}
	for (i = 1; i <= PHILOS; i++)
		if (pthread_join (philo[i], NULL) != 0)
			return(ft_error("Failed to join thread\n", 5));
	return 0;
	
	
	
	
	
	// int	i;

	// if (argc == 2)
	// 	sleep_seconds = ft_atoi(argv[1]);
	// i = 0;
	// pthread_mutex_init(&mutex_food, NULL);
	// i = 0;
	// while (++i <= PHILOS)
	// 	if (pthread_mutex_init(&mutex_fork[i], NULL) != 0)
	// 		return(ft_error("Failed to create a mutex\n", 3));
	// i = 0;
	// while (++i <= PHILOS)
	// 	if (pthread_create(&philo[i], NULL, philosopher, (void *)&i) != 0)
	// 		return(ft_error("Failed to create thread\n", 4));
	// i = 0;
	// while (++i <= PHILOS)
	// 	if (pthread_join(philo[i], NULL) != 0)
	// 		return(ft_error("Failed to join thread\n", 5));
	// pthread_mutex_destroy(&mutex_food);
	// i = 0;
	// while (++i <= PHILOS)
	// 	pthread_mutex_destroy(&mutex_fork[i]);
	// return (0);
}

void *philosopher(void *num)
{
	int	id; 
	int	left_fork, right_fork, f;

	id = *(int*)num;
	//printf ("Philosopher %d is done thinking and now ready to eat.\n", id);
	right_fork = id;
	left_fork = id + 1;
	if (left_fork == PHILOS)
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

	pthread_mutex_lock(&mutex_food);
	if (food > 0)
		food--;
	myfood = food;
	pthread_mutex_unlock(&mutex_food);
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