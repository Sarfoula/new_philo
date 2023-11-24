/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:12:50 by yallo             #+#    #+#             */
/*   Updated: 2023/11/24 12:07:11 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->eating, NULL);
	pthread_mutex_init(&data->dead, NULL);
}

void init_data(t_data *data, char **argv)
{
	data->dead_flag = 1;
	data->must_eat = -1;
	data->start_time = get_time();
	data->nbr_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->must_eat = ft_atoi(argv[5]);
}

int init_philos(t_philo *philos, t_data *data, char **argv)
{
	int	nbr_philo;
	int	i;

	nbr_philo = ft_atoi(argv[1]);
	i = 0;
	while (i < nbr_philo)
	{
		philos[i].dead_flag = &data->dead_flag;
		philos[i].id = i + 1;
		philos[i].fork = 1;
		philos[i].m_fork = &data->forks[i];
		philos[i].next_fork = &philos[(i + 1) % nbr_philo].fork;
		philos[i].m_next_fork = &data->forks[(i + 1) % nbr_philo];
		philos[i].meal_eaten = 0;
		philos[i].dead = &data->dead;
		philos[i].eating = &data->eating;
		philos[i].data = data;
		i++;
	}
	return (0);
}

int	init(t_data *data, t_philo *philos, char **argv)
{
	init_data(data, argv);
	init_mutex(data);
	init_philos(philos, data, argv);
	data->philos = philos;
	return (0);
}
