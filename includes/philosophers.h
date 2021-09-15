/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:45:51 by julian            #+#    #+#             */
/*   Updated: 2021/09/15 13:06:18 by julian           ###   ########.fr       */
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

/*
** nop	- number of philosophers
** ttd	- time to die [ms]
** tte	- time to eat [ms]
** tts	- time toe sleep [ms]
** noms	- number of must eat
*/

typedef struct s_input
{
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				nome;
	long long		start_time;
	pthread_mutex_t	mutex_fork[242];
	pthread_mutex_t	mutex_printing;
	t_philo			philos[242];
}			t_input;

typedef struct	s_philo
{
	int			id;
	int			right_fork;
	int			left_fork;
	int			eat_count;
	long long	last_meal;
	pthread_t	thread;
	t_input		input;
}				t_philo;

int			check_input(int argc, char *argv[]);
int			ft_atoi(const char *str);
long long	get_timestamp();

#endif
