/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:48:08 by julian            #+#    #+#             */
/*   Updated: 2021/09/27 18:10:29 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// int				nop;
// int				ttd;
// int				tte;
// int				tts;
// int				nome;
// int				*a;
// long long		start_time;
// pthread_mutex_t	mutex_fork[242];
// pthread_mutex_t	mutex_printing;
// pthread_t		philo[242];

void	printing(t_data *data, t_philo *philo, char *s)
{
	pthread_mutex_lock(&(data->mutex_printing));
	printf("%lld\t", get_time() - philo->start_time);
	printf("%d %s", philo->id, s);
	pthread_mutex_unlock(&(data->mutex_printing));
}

void	optimized_sleep(int stop_sleeping)
{
	long long	start_sleeping;
	long long	sleep;

	start_sleeping = get_time();
	sleep = 0;
	while (sleep <= stop_sleeping)
	{
		sleep = get_time() - start_sleeping;
		usleep(100);
	}
}

void	eating(t_data *data, t_philo *philo)
{
	int forks[2];
	
	forks[0] = philo->id;
	forks[1] = (philo->id + 1) % data->nop;
	pthread_mutex_lock(&(data->mutex_fork[forks[0]]));
	if (data->died == 1)
	{
		pthread_mutex_unlock(&(data->mutex_fork[forks[0]]));
		return ;
	}
	printing(data, philo, "has taken a fork\n");
	if (data->nop == 1)
	{
		while (data->died != 1)
			usleep(100);
		return ;
	}
	pthread_mutex_lock(&(data->mutex_fork[forks[1]]));
	if (data->died == 1)
	{
		pthread_mutex_unlock(&(data->mutex_fork[forks[0]]));
		pthread_mutex_unlock(&(data->mutex_fork[forks[1]]));
			return ;
	}
	printing(data, philo, "has taken a fork\n");
	printing(data, philo, "is eating\n");
	pthread_mutex_lock(&data->mutex_time);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&data->mutex_time);	
	optimized_sleep(data->tte);
	pthread_mutex_unlock(&(data->mutex_fork[forks[0]]));
	pthread_mutex_unlock(&(data->mutex_fork[forks[1]]));
}

void	*death_checker(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;

	pthread_mutex_lock(&data->mutex_time);
	while (get_time() - philo->last_meal <= data->ttd)
	{
		pthread_mutex_unlock(&data->mutex_time);
		usleep(100);
		pthread_mutex_lock(&data->mutex_time);
	}
	pthread_mutex_unlock(&data->mutex_time);
	if (philo->eat_count == 0)
		return (NULL);
	pthread_mutex_lock(&data->mutex_death);
	if (data->died == 1)
	{
		pthread_mutex_unlock(&data->mutex_death);
		return (NULL);
	}
	printing(data, philo, "died\n");
	data->died = 1;
	pthread_mutex_unlock(&data->mutex_death);
	return (NULL);
}

void	*philosopher(void *arg)
{
	t_philo		*philo;
	t_data		*data;
	pthread_t	death;

	philo = (t_philo *)arg;
	data = philo->data;
	philo->start_time = get_time();
	philo->last_meal = philo->start_time;
	pthread_create(&death, NULL, death_checker, philo);
	if (philo->id % 2 == 0)
		usleep(10000);
	while (philo->eat_count)
	{
		if (data->died == 1)
			break ;
		eating(data, philo);
		if (data->died == 1)
			break ;
		if (philo->eat_count > 0)
			philo->eat_count--;
		if (philo->eat_count == 0)
			break ;
		printing(data, philo, "is sleeping\n");
		optimized_sleep(data->tts);
		if (data->died == 1)
			break ;
		printing(data, philo, "is thinking\n");
	}
	pthread_join(death, NULL);
	return (NULL);
}

void	init_philosophers(t_data *data, t_philo *philo, int i)
{
		philo[i].id = i + 1;
		philo[i].eat_count = data->nome;
		philo[i].last_meal = 0;
		philo[i].data = data;
}

int	create_run_threads(t_data *data)
{
	int			i;
	t_philo		*philo;
	pthread_t	*thread;
	
	if (!(philo = (t_philo *)malloc(sizeof(t_philo) * data->nop)))
		return (1);
	if (!(thread = (pthread_t *)malloc(sizeof(pthread_t) * data->nop)))
		return (1);
	i = -1;
	while (++i < data->nop)
	{
		init_philosophers(data, philo, i);
		if (pthread_create(&thread[i], NULL, philosopher, &philo[i]) != 0)
			return(printf("Failed to create thread\n"));
	}
	i = -1;
	while (++i < data->nop)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (printf("Failed to join thread %d\n", i));
		//printf("Thread %d has finished execution\n", i);
		pthread_mutex_destroy(&(data->mutex_fork[i]));
	}
	pthread_mutex_destroy(&(data->mutex_printing));
	pthread_mutex_destroy(&(data->mutex_death));
	pthread_mutex_destroy(&(data->mutex_time));
	free(philo);
	free(thread);
	return (0);
}

int	create_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&(data->mutex_printing), NULL) != 0)
			return(printf("Failed to create mutex_print\n"));
	if (pthread_mutex_init(&(data->mutex_death), NULL) != 0)
			return(printf("Failed to create mutex_death\n"));
	if (pthread_mutex_init(&(data->mutex_time), NULL) != 0)
			return(printf("Failed to create mutex_time\n"));
	i = -1;
	while (++i <= data->nop)
		if (pthread_mutex_init(&(data->mutex_fork[i]), NULL) != 0)
			return(printf("Failed to create mutex_fork[%d]\n", i));
	return (0);
}

int	get_data(int argc, char *argv[], t_data *data)
{
	data->nop = ft_atoi(argv[1]);
	data->ttd = ft_atoi(argv[2]);
	data->tte = ft_atoi(argv[3]);
	data->tts = ft_atoi(argv[4]);
	if (data->ttd < 0 || data->tte < 0 || data->tts < 0)
		return (2);
	if (argc == 6)
	{
		data->nome = ft_atoi(argv[5]);
		if (data->nome < 1)
			return (2);
	}
	else 
		data->nome = -1;
	data->died = 0;
	return (0);
}

int main(int argc, char *argv[])
{	
	t_data	data;
	
	if (check_input(argc, argv) != 0)
		return (1);
	if (get_data(argc, argv, &data) != 0)
		return (2);
	if (create_mutex(&data) != 0)
		return (3);
	if (create_run_threads(&data) != 0)
		return (4);
	//system("leaks philo");
	return (0);
}
