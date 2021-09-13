/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:48:08 by julian            #+#    #+#             */
/*   Updated: 2021/09/13 17:29:00 by julian           ###   ########.fr       */
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

pthread_mutex_t	pitchfork[PHILOS];
pthread_t		philo[PHILOS];
pthread_mutex_t	food_lock;;
int	sleep_seconds = 0;

int main(int argc, char *argv[])
{
	int	i;

	
	if (argc == 2)
		sleep_seconds = ft_atoi(argv[1]);
	i = 0;
	pthread_mutex_init(&food_lock, NULL);
	i = 0;
	while (++i <= PHILOS)
	{
		if (pthread_mutex_init(&pitchfork[i], NULL) != 0)
		{
			perror("Failed to create a mutex\n");
			return (2);
		}
	}
	i = 0;
	while (++i <= PHILOS)
	{
		if (pthread_create(&philo[i], NULL, philosopher, (void *)&i) != 0)
		{
			perror("Failed to create thread\n");
			return (2);
		}
	}
	i = 0;
	while (++i <= PHILOS)
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
	//char	*s_id;
	// int	id_copy;
	int	left_fork, right_fork, f;

	id = *(int*)num;
	// id_copy = id;
	//s_id = ft_itoa(id);
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
		// while (id_copy)
		// {
		// 	ft_putchar('0');
		// 	id_copy /= 10;
		// }
		//ft_putstr(" is eating\n");
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

	pthread_mutex_lock(&food_lock);
	if (food > 0)
		food--;
	myfood = food;
	pthread_mutex_unlock(&food_lock);
	return (myfood);
}

void	grab_fork(int phil, int c)
{
	pthread_mutex_lock(&pitchfork[c]);
	printf ("%d has taken a fork\n", phil);
}

void	down_forks(int c1, int c2)
{
	pthread_mutex_unlock(&pitchfork[c1]);
	pthread_mutex_unlock(&pitchfork[c2]);
}