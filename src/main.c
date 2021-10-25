/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:48:08 by julian            #+#    #+#             */
/*   Updated: 2021/10/25 13:51:42 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
