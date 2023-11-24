/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:31:33 by yallo             #+#    #+#             */
/*   Updated: 2023/11/24 12:18:13 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void waiting(t_philo *philo)
{
	while (1)
	{
		usleep(1000);
		pthread_mutex_lock(philo->dead);
		if (*philo->dead_flag == 0)
		{
			pthread_mutex_unlock(philo->dead);
			break;
		}
		pthread_mutex_unlock(philo->dead);
	}
}

int eating(t_philo *philo)
{
	if (take_fork(philo->m_fork, &philo->fork) == 1)
		return (1);
	if (ft_prompt(philo, "has taken a fork") == 1)
		return (1);
	if (take_fork(philo->m_next_fork, philo->next_fork) == 1)
		return (1);
	if (ft_prompt(philo, "has taken a fork") == 1)
		return (1);
	if (ft_prompt(philo, "is eating") == 1)
		return (1);
	pthread_mutex_lock(philo->eating);
	philo->meal_eaten++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->eating);
	ft_usleep(philo->data->time_to_eat, philo);
	free_forks(philo);
	return (0);
}

int sleeping(t_philo *philo)
{
	if (ft_prompt(philo, "is sleeping") == 1)
		return (1);
	ft_usleep(philo->data->time_to_sleep, philo);
	return (0);
}

int thinking(t_philo *philo)
{
	if (ft_prompt(philo, "is thinking") == 1)
		return (1);
	return (0);
}

void *routine(void *pointer)
{
	t_philo *philo;

	philo = (t_philo *)pointer;
	waiting(philo);
	pthread_mutex_lock(philo->eating);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->eating);
	if (philo->id % 2 == 0)
		usleep(philo->data->nbr_philo * 500);
	while (1)
	{
		if (eating(philo) == 1)
			break ;
		if (sleeping(philo) == 1)
			break ;
		if (thinking(philo) == 1)
			break ;
	}
	return (0);
}
