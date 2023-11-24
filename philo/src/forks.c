/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 05:47:57 by yallo             #+#    #+#             */
/*   Updated: 2023/11/24 16:44:09 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	dead_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->dead);
	if (*philo->dead_flag == 1)
	{
		pthread_mutex_unlock(philo->dead);
		return (1);
	}
	pthread_mutex_unlock(philo->dead);
	return (0);
}

int	take_fork(t_philo *philo, pthread_mutex_t *m_fork, int *fork)
{
	while (!dead_philo(philo))
	{
		pthread_mutex_lock(m_fork);
		if (*fork == 1)
		{
			*fork = 0;
			pthread_mutex_unlock(m_fork);
			ft_prompt(philo, "has taken a fork");
			return (0);
		}
		pthread_mutex_unlock(m_fork);
		usleep(1000);
	}
	return (1);
}

void	free_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->m_next_fork);
	*philo->next_fork = 1;
	pthread_mutex_unlock(philo->m_next_fork);
	pthread_mutex_lock(philo->m_fork);
	philo->fork = 1;
	pthread_mutex_unlock(philo->m_fork);
}
