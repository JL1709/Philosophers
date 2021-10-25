#include "../includes/philosophers.h"

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
