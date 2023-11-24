/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:46:29 by yallo             #+#    #+#             */
/*   Updated: 2023/11/24 12:21:01 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	ft_atoi(const char *str)
{
	size_t	i;
	long	result;
	int		sign;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + str[i] - 48;
		if (result != ((result * 10 + str[i] - 48) / 10) && sign == -1)
			return (0);
		if (result != ((result * 10 + str[i] - 48) / 10) && sign == 1)
			return (-1);
		i++;
	}
	return ((result * sign));
}

size_t	get_time(void)
{
	struct timeval current;

	if (gettimeofday(&current, NULL) == -1)
		return (write(2, "Error in gettimofday()\n", 23), 1);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

int ft_prompt(t_philo *philo, char *display)
{
	size_t	start;

	start = philo->data->start_time;
	pthread_mutex_lock(philo->dead);
	if (*philo->dead_flag == 0)
	{
		printf("%lu %d %s\n", get_time() - start, philo->id, display);
		pthread_mutex_unlock(philo->dead);
		return (0);
	}
	pthread_mutex_unlock(philo->dead);
	return (1);
}

void ft_usleep(size_t time, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < time)
	{
		usleep(1000);
		pthread_mutex_lock(philo->dead);
		if (*philo->dead_flag == 1)
		{
			pthread_mutex_unlock(philo->dead);
			break;
		}
		pthread_mutex_unlock(philo->dead);
	}
}

