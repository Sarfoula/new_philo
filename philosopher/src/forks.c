/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 05:47:57 by yallo             #+#    #+#             */
/*   Updated: 2023/11/24 06:00:37 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	pthread_mutex_lock(philo->m_next_fork);
	*philo->next_fork = 1;
	pthread_mutex_unlock(philo->m_next_fork);
	pthread_mutex_lock(philo->m_fork);
	philo->fork = 1;
	pthread_mutex_unlock(philo->m_fork);
}
