/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:45:51 by julian            #+#    #+#             */
/*   Updated: 2021/10/25 14:06:45 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

/*
** nop	- number of philosophers
** ttd	- time to die [ms]
** tte	- time to eat [ms]
** tts	- time toe sleep [ms]
** noms	- number of must eat
*/

typedef struct s_data
{
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				nome;
	int				died;
	pthread_mutex_t	mutex_fork[242];
	pthread_mutex_t	mutex_printing;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_time;
}			t_data;

typedef struct s_philo
{
	int				id;
	long long		start_time;
	int				eat_count;
	long long		last_meal;
	t_data			*data;
}				t_philo;

int			check_input(int argc, char *argv[]);
int			get_data(int argc, char *argv[], t_data *data);
int			ft_atoi(const char *str);
long long	get_time(void);
void		init_philosophers(t_data *data, t_philo *philo, int i);
void		optimized_sleep(int stop_sleeping);
void		printing(t_data *data, t_philo *philo, char *s);
int			create_mutex(t_data *data);
int			create_run_threads(t_data *data);
void		*run_philosopher(void *arg);
void		eating(t_data *data, t_philo *philo);
void		*death_checker(void *arg);

#endif
