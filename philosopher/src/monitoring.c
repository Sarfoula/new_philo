/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:30:21 by yallo             #+#    #+#             */
/*   Updated: 2023/11/23 18:54:23 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->eating);
	if (get_time() - philo->last_meal >= philo->data->time_to_die)
	{
		pthread_mutex_unlock(philo->eating);
		return (1);
	}
	pthread_mutex_unlock(philo->eating);
	return (0);
}

int	check_eating(t_philo *philos)
{
	int	i;
	int	finish_eating;

	i = 0;
	finish_eating = 0;
	if (philos->data->must_eat == -1)
		return (0);
	while (i < philos->data->nbr_philo)
	{
		pthread_mutex_lock(philos->eating);
		if (philos[i].meal_eaten == philos->data->must_eat)
			finish_eating++;
		pthread_mutex_unlock(philos->eating);
		i++;
	}
	if (finish_eating == philos->data->nbr_philo)
	{
		pthread_mutex_lock(philos->dead);
		philos->data->dead_flag = 1;
		pthread_mutex_unlock(philos->dead);
		return (1);
	}
	return (0);
}

int	check_death(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->nbr_philo)
	{
		if (is_dead(&philos[i]) == 1)
		{
			ft_prompt(&philos[i], "died");
			pthread_mutex_lock(philos->dead);
			philos->data->dead_flag = 1;
			pthread_mutex_unlock(philos->dead);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitoring(t_philo *philos)
{
	pthread_mutex_lock(philos->dead);
	philos->data->dead_flag = 0;
	pthread_mutex_unlock(philos->dead);
	while (1)
	{
		if (check_death(philos) == 1 || check_eating(philos) == 1)
			break ;
	}
	return (0);
}
