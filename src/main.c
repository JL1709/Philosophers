/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:48:08 by julian            #+#    #+#             */
/*   Updated: 2021/09/15 13:11:10 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int				nop;
int				ttd;
int				tte;
int				tts;
int				nome;
int				*a;
long long		start_time;
pthread_mutex_t	mutex_fork[242];
pthread_mutex_t	mutex_printing;
pthread_t		philo[242];


void	destroy_mutex_forks(void)
{
	int	i;

	i = 0;
	while (++i <= nop)
		pthread_mutex_destroy(&mutex_fork[i]);
}

int	join_threads(void)
{
	int	i;

	i = 0;
	while (++i < nop)
	{
		if (pthread_join(philo[i], NULL) != 0)
			return (printf("Failed to join thread %d\n", i));
		printf("Thread %d has finished execution\n", i);
	}
	return (0);
}

void	printing(int id, char *s)
{
	pthread_mutex_lock(&mutex_printing);
	printf("%lld ", get_timestamp() - start_time);
	printf("%d %s", id, s);
	pthread_mutex_unlock(&mutex_printing);
}

void	grab_fork(int phil, int c)
{
	pthread_mutex_lock(&mutex_fork[c]);
	printing(phil, "has taken a fork\n");
}

void	down_forks(int c1, int c2)
{
	pthread_mutex_unlock(&mutex_fork[c1]);
	pthread_mutex_unlock(&mutex_fork[c2]);
}

void	*philosopher(void *data)
{
	int		i;
	t_philo	*philo;
	t_input	*input;

	i = 0;
	philo = (t_philo *)data;
	input = philo->input;
	
	if (philo->id % 2 == 0)
		usleep(10000);
	while (1)
	{
		grab_fork(id, right_fork);
		grab_fork(id, left_fork);
		printing(id, "is eating\n");
		usleep(tte);
		if (eat_count == nome)
			break ;
		down_forks(left_fork, right_fork);
		printing(id, "is sleeping\n");
		usleep(tts);
		printing(id, "is thinking\n");
	}
	return (NULL);
}

int	create_run_threads(t_input *input)
{
	int		i;
	t_philo	*philo;
	
	i = 0;
	philo = input->philos;
	input->start_time = get_timestamp();
	while (++i <= input->nop)
	{
		if (pthread_create(&(philo[i].thread), NULL, &philosopher, &(philo[i])) != 0)
			return(printf("Failed to create thread\n"));
	}
	return (0);
}

int	create_mutex(t_input *input)
{
	int	i;

	if (pthread_mutex_init(&mutex_printing, NULL) != 0)
			return(printf("Failed to create mutex_print\n"));
	i = 0;
	while (++i <= input->nop)
		if (pthread_mutex_init(&(input->mutex_fork[i]), NULL) != 0)
			return(printf("Failed to create mutex_fork[%d]\n", i));
	return (0);
}

void	init_philosophers(t_input *input)
{
	int	i;

	i = -1;
	while (++i < input->nop)
	{
		input->philos[i].id = i;
		input->philos[i].right_fork = i;
		input->philos[i].left_fork = (i + 1) % input->nop;
		input->philos[i].eat_count = 0;
		input->philos[i].last_meal = 0;
		input->philos[i].input = input;
	}
}

int	get_input(int argc, char *argv[], t_input *input)
{
	input->nop = ft_atoi(argv[1]);
	input->ttd = ft_atoi(argv[2]) * 1000;
	input->tte = ft_atoi(argv[3]) * 1000;
	input->tts = ft_atoi(argv[4]) * 1000;
	if (input->nop < 2 || input->ttd < 0 || input->tte < 0 || input->tts < 0)
		return (2);
	if (argc == 6)
	{
		input->nome = ft_atoi(argv[5]);
		if (input->nome < 1)
			return (2);
	}
	return (0);
}

int main(int argc, char *argv[])
{	
	t_input	input;
	
	if (check_input(argc, argv) != 0)
		return (1);
	if (get_input(argc, argv, &input) != 0)
		return (2);
	init_philosophers(&input);
	if (create_mutex(&input) != 0)
		return (3);
	if (create_run_threads() != 0)
	{
		pthread_mutex_destroy(&mutex_printing);
		destroy_mutex_forks();
		return (4);
	}
	if (join_threads() != 0)
	{
		pthread_mutex_destroy(&mutex_printing);
		destroy_mutex_forks();
		return (5);
	}
	pthread_mutex_destroy(&mutex_printing);
	destroy_mutex_forks();
	system("leaks philo");
	return (0);
}
