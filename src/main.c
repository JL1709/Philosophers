/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:48:08 by julian            #+#    #+#             */
/*   Updated: 2021/09/22 16:52:41 by julian           ###   ########.fr       */
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

void	printing(t_data *data, int id, char *s)
{
	pthread_mutex_lock(&(data->mutex_printing));
	printf("%lld ", get_time() - data->start_time);
	printf("%d %s", id, s);
	pthread_mutex_unlock(&(data->mutex_printing));
}

void	grab_fork(t_data *data, int phil, int c)
{
	pthread_mutex_lock(&(data->mutex_fork[c]));
	printing(data, phil, "has taken a fork\n");
}

void	down_forks(t_data *data, int c1, int c2)
{
	pthread_mutex_unlock(&(data->mutex_fork[c1]));
	pthread_mutex_unlock(&(data->mutex_fork[c2]));
}

void	*philosopher(void *arg)
{
	int		i;
	t_philo	*philo;
	t_data	*data;

	i = 0;
	philo = (t_philo *)arg;
	data = philo->data;
	printf("id = %d\n", philo->id);
	printf("ttd = %d\n", data->ttd);
	philo->start_time = get_time();
	
	// if (philo->id % 2 == 0)
	// 	usleep(10000);
	// while (1)
	// {
	// 	grab_fork(data, philo->id, philo->right_fork);
	// 	grab_fork(data, philo->id, philo->left_fork);
	// 	printing(data, philo->id, "is eating\n");
	// 	usleep(data->tte);
	// 	if (philo->eat_count == data->nome)
	// 		break ;
	// 	down_forks(data, philo->left_fork, philo->right_fork);
	// 	printing(data, philo->id, "is sleeping\n");
	// 	usleep(data->tts);
	// 	printing(data, philo->id, "is thinking\n");
	// }
	return (NULL);
}

void	init_philosophers(t_data *data, t_philo *philo, int i)
{
		philo[i].id = i;
		philo[i].right_fork = i;
		philo[i].left_fork = (i + 1) % data->nop;
		philo[i].eat_count = 0;
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
		if (pthread_create(&thread[i], NULL, &philosopher, &philo[i]) != 0)
			return(printf("Failed to create thread\n"));
	}
	i = -1;
	while (++i < data->nop)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (printf("Failed to join thread %d\n", i));
		//printf("Thread %d has finished execution\n", i);
	}
	i = -1;
	while (++i < data->nop)
		pthread_mutex_destroy(&(data->mutex_fork[i]));
	pthread_mutex_destroy(&(data->mutex_printing));
	free(philo);
	free(thread);
	return (0);
}

int	create_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&(data->mutex_printing), NULL) != 0)
			return(printf("Failed to create mutex_print\n"));
	i = -1;
	while (++i <= data->nop)
		if (pthread_mutex_init(&(data->mutex_fork[i]), NULL) != 0)
			return(printf("Failed to create mutex_fork[%d]\n", i));
	return (0);
}

int	get_data(int argc, char *argv[], t_data *data)
{
	data->nop = ft_atoi(argv[1]);
	data->ttd = ft_atoi(argv[2]) * 1000;
	data->tte = ft_atoi(argv[3]) * 1000;
	data->tts = ft_atoi(argv[4]) * 1000;
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
