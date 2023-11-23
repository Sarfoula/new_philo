/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:04:12 by yallo             #+#    #+#             */
/*   Updated: 2023/11/23 18:57:45 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"



int main(int argc, char **argv)
{
	t_data	data;
	t_philo	philos;

 	if (argc != 5 && argc != 6)
		return (write(2, "Error: Wrong number of arguments\n", 33), 0);
	if (parse(argc, argv) == 1)
		return (0);
	if(init(&data, &philos, argv) == 1)
		return (0);
	create_threads(&data);
	monitoring(data.philos);
	join_threads(&data);
	free_all(&data, &philos, NULL);
	return (0);
}
