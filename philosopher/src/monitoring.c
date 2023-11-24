/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:30:21 by yallo             #+#    #+#             */
/*   Updated: 2023/11/24 12:11:13 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->eating);
	if (get_time() - philo->last_meal >= philo->data->time_to_die)
	{
		ft_prompt(philo, "died");
		pthread_mutex_unlock(philo->eating);
		return (1);
	}
	pthread_mutex_unlock(philo->eating);
	return (0);
}

int	check_eating(t_philo *philos)
{
	pthread_mutex_lock(philos->eating);
	if (philos->data->must_eat == -1)
	{
		pthread_mutex_unlock(philos->eating);
		return (0);
	}
	if (philos->meal_eaten >= philos->data->must_eat)
	{
		pthread_mutex_unlock(philos->eating);
		return (1);
	}
	pthread_mutex_unlock(philos->eating);
	return (0);
}

int	monitoring(t_data *data)
{
	int	i;
	int	finished;

	while (1)
	{
		i = 0;
		finished = 0;
		usleep(1000);
		while (i < data->nbr_philo)
		{
			if (is_dead(&data->philos[i]) == 1)
				return (1);
			finished += check_eating(&data->philos[i]);
			if (finished == data->nbr_philo)
				return (1);
			i++;
		}
	}
}
