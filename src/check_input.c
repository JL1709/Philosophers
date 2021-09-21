/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 11:06:09 by julian            #+#    #+#             */
/*   Updated: 2021/09/21 15:01:10 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

static void	print_error(int i)
{
	if (i == 1)
	{
		printf(YELLOW"Usage: "RESET);
		printf("./philo ");
		printf("\"number_of_philosophers\" ");
		printf("\"time_to_die [ms]\" ");
		printf("\"time_to_eat [ms]\" ");
		printf("\"time_to_sleep [ms]\" ");
		printf(CYAN"\"[number_of_times_each_philosopher_must_eat]\" ");
		printf("(optional)\n"RESET);
	}
	if (i == 2)
	{
		printf(MAGENTA"All arguments must be positiv numbers!\n"RESET);
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
