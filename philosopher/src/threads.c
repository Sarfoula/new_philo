/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:28:55 by yallo             #+#    #+#             */
/*   Updated: 2023/11/23 18:51:40 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int create_threads(t_data *data)
{
	size_t		start;
	int			i;

	i = 0;
	start = get_time();
	data->start_time = start;
	while (i < data->nbr_philo)
	{
		data->philos[i].last_meal = start;
		if (pthread_create(&data->philos[i].thread, NULL, &routine, (void *) &data->philos[i]) != 0)
			return (free_all(data, data->philos, "Error failed to create thread\n"), 1);
		i++;
	}
	return (0);
}

int join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (free_all(data, data->philos, "Error failed to join thread\n"), 1);
		i++;
	}
	return (0);
}
