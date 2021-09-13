/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 11:06:09 by julian            #+#    #+#             */
/*   Updated: 2021/09/13 17:19:49 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	print_error(int i)
{
	if (i == 1 )
	{
		ft_putstr("Usage: ");
		ft_putstr("./philo ");
		ft_putstr("\"number_of_philosophers\" ");
		ft_putstr("\"time_to_die [ms]\" ");
		ft_putstr("\"time_to_eat [ms]\" ");
		ft_putstr("\"time_to_sleep [ms]\" ");
		ft_putstr("\"[number_of_times_each_philosopher_must_eat] ");
		ft_putstr("(optional)\"\n");
	}
	if (i == 2)
	{
		ft_putstr("arguments must be numbers only!\n");
	}
}

int	check_input(int argc, char *argv[])
{
	int	i;
	int	j;
	
	if (argc < 5 || argc > 6)
	{
		print_error(1);
		return (1);
	}
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j] != '\0')
		{
			if (ft_isdigit(argv[i][j]) != 1)
			{
				print_error(2);
				return (2);
			}
		}
	}
	return (0);
}
