/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:04:12 by yallo             #+#    #+#             */
/*   Updated: 2023/11/24 12:26:18 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int main(int argc, char **argv)
{
	t_data			data;
	t_philo			philo[MAX_PHILO];
	pthread_mutex_t	forks[MAX_PHILO];

	data.philos = philo;
	data.forks = forks;
	if (argc != 5 && argc != 6)
		return (write(2, "Error: Wrong number of arguments\n", 33), 0);
	if (check_args(argc, argv) == 1)
		return (0);
	if (init(&data, philo, argv) == 1)
		return (0);
	create_threads(&data);
	if (monitoring(&data) == 1)
	{
		pthread_mutex_lock(&data.dead);
		data.dead_flag = 1;
		pthread_mutex_unlock(&data.dead);
	}
	join_threads(&data);
	return (0);
}
