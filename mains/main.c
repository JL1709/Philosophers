/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:48:08 by julian            #+#    #+#             */
/*   Updated: 2021/09/13 16:45:59 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philosophers.h"

#define PHILOS 5
#define DELAY 5000
#define FOOD 50

void	*philosopher(void *id);
void	grab_fork(int phil, int c, char *hand);
void	down_forks(int c1, int c2);
int		food_on_table(void);

pthread_mutex_t	fork[PHILOS];
pthread_t		philo[PHILOS];
pthread_mutex_t	food_lock;;
int	sleep_seconds = 0;

int main(int argc, char *argv[])
{
	int	i;

	
	if (argc == 2)
		sleep_seconds = ft_atoi(argv[1]);
	i = -1;
	pthread_mutex_init(&food_lock, NULL);
	i = -1;
	while (++i < PHILOS)
	{
		if (pthread_mutex_init(&fork[i], NULL) != 0)
		{
			perror("Failed to create a mutex\n");
			return (2);
		}
	}
	i = -1;
	while (++i < PHILOS)
	{
		if (pthread_create(&philo[i], NULL, philosopher, (void *)&i) != 0)
		{
			perror("Failed to create thread\n");
			return (2);
		}
	}
	i = -1;
	while (++i < 5)
	{
		if (pthread_join(philo[i], NULL) != 0)
		{
			perror("Failed to join thread\n");
			return (3);
		}
	}
	return (0);
}

void *philosopher(void *num)
{
	int	id; 
	int	left_fork, right_fork, f;

	id = *(int*)num;
	printf ("Philosopher %d is done thinking and now ready to eat.\n", id);
	right_fork = id;
	left_fork = id + 1;
	if (left_fork == PHILOS)
		left_fork = 0;
	while ((f = food_on_table()))
	{
		if (id == 1)
			sleep(sleep_seconds);
		grab_fork(id, right_fork, "right");
		grab_fork(id, left_fork, "left");
		printf ("Philosopher %d: eating.\n", id);
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

	pthread_mutex_lock(&food_lock);
	if (food > 0)
		food--;
	myfood = food;
	pthread_mutex_unlock(&food_lock);
	return (myfood);
}

void	grab_fork(int phil, int c, char *hand)
{
	pthread_mutex_lock(&fork[c]);
	printf ("Philosopher %d: got %s fork %d\n", phil, hand, c);
}

void	down_forks(int c1, int c2)
{
	pthread_mutex_unlock(&fork[c1]);
	pthread_mutex_unlock(&fork[c2]);
}