/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:31:33 by yallo             #+#    #+#             */
/*   Updated: 2023/11/23 18:51:26 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead);
	if (philo->data->dead_flag == 1)
	{
		pthread_mutex_unlock(philo->dead);
		return (1);
	}
	pthread_mutex_unlock(philo->dead);
	return (0);
}

int take_fork(pthread_mutex_t *m_fork, int *fork)
{
	while (1)
	{
		pthread_mutex_lock(m_fork);
		if (*fork == 1)
		{
			*fork = 0;
			pthread_mutex_unlock(m_fork);
			return (0);
		}
		pthread_mutex_unlock(m_fork);
		usleep(1000);
	}
}

void free_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->m_fork);
	philo->fork = 1;
	pthread_mutex_unlock(philo->m_fork);
	pthread_mutex_lock(philo->m_next_fork);
	*philo->next_fork = 1;
	pthread_mutex_unlock(philo->m_next_fork);
}

void eating(t_philo *philo)
{
	if (take_fork(philo->m_fork, &philo->fork) == 1)
		return ;
	ft_prompt(philo, "has taken a fork");
	if (take_fork(philo->m_next_fork, philo->next_fork) == 1)
		return ;
	ft_prompt(philo, "has taken a fork");
	ft_prompt(philo, "is eating");
	pthread_mutex_lock(philo->eating);
	philo->meal_eaten++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->eating);
	ft_usleep(philo->data->time_to_eat);
	free_forks(philo);
}

void sleeping(t_philo *philo)
{
	ft_prompt(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void thinking(t_philo *philo)
{
	ft_prompt(philo, "is thinking");
}

void waiting_monitor(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->dead);
		if (philo->data->dead_flag == 0)
		{
			pthread_mutex_unlock(philo->dead);
			break;
		}
		pthread_mutex_unlock(philo->dead);
		usleep(1000);
	}
}

void *routine(void *pointer)
{
	t_philo *philo;

	philo = pointer;
	waiting_monitor(philo);
	if (philo->id % 2 == 0)
		usleep(philo->data->nbr_philo * 500);
	while (dead_loop(philo) == 0)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (0);
}
