/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:46:29 by yallo             #+#    #+#             */
/*   Updated: 2023/11/23 18:56:53 by yallo            ###   ########.fr       */
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

long int	get_time(void)
{
	struct timeval current;

	if (gettimeofday(&current, NULL) == -1)
		return (write(2, "Error in gettimofday()\n", 23), 1);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

void ft_prompt(t_philo *philo, char *display)
{
	size_t	start;

	start = philo->data->start_time;
	pthread_mutex_lock(&philo->data->dead);
	if (philo->data->dead_flag == 0)
	{
		pthread_mutex_unlock(&philo->data->dead);
		pthread_mutex_lock(philo->prompt);
		printf("%lu %d %s\n", start - get_time(), philo->id, display);
		pthread_mutex_unlock(philo->prompt);
		return ;
	}
	pthread_mutex_unlock(&philo->data->dead);
}

void ft_usleep(size_t time)
{
	size_t	start;

	start = get_time();
	while (start - get_time() < time)
		usleep(1000);
}

void free_all(t_data *data, t_philo *philos, char *display)
{
	int	i;

	i = 0;
	if (display)
	{
		while (display[i])
			i++;
		write(2, &display, i);
	}
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->eating);
	pthread_mutex_destroy(&data->prompt);
	free(philos);
	free(data);
}
