/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 11:06:09 by julian            #+#    #+#             */
/*   Updated: 2021/09/22 16:25:12 by julian           ###   ########.fr       */
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
		printf(YELLOW"All arguments must be positiv numbers!\n"RESET);
	if (i == 3)
		printf(YELLOW"Nice try, but go with at least one philosopher.\n"RESET);
}

static int	only_pos_nbrs(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		if (argv[i][0] == '+')
			j++;
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

int	check_input(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		print_error(1);
		return (1);
	}
	if (only_pos_nbrs(argc, argv) != 0)
		return (2);
	if (ft_atoi(argv[1]) < 1)
	{
		print_error(3);
		return (3);
	}
	return (0);
}
