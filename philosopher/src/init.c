/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:12:50 by yallo             #+#    #+#             */
/*   Updated: 2023/11/23 18:59:02 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void init_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	if (!data->forks)
		return ;
	pthread_mutex_init(&data->eating, NULL);
	pthread_mutex_init(&data->prompt, NULL);
	pthread_mutex_init(&data->dead, NULL);
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
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
	philos = malloc(sizeof(philos) * nbr_philo);
	if (!philos)
		return (write(2, "Malloc philos failed\n", 22), 1);
	i = 0;
	while (i < nbr_philo)
	{
		philos[i].id = i + 1;
		philos[i].fork = 1;
		philos[i].m_fork = &data->forks[i];
		philos[i].next_fork = &philos[i + 1].fork;
		philos[i].m_next_fork = &data->forks[i + 1];
		philos[i].meal_eaten = 0;
		philos[i].dead = &data->dead;
		philos[i].eating = &data->eating;
		philos[i].prompt = &data->prompt;
		i++;
	}
	return (0);
}

int	init(t_data *data, t_philo *philos, char **argv)
{
	init_data(data, argv);
	init_mutex(data);
	if (init_philos(philos, data, argv) == 1)
		return (1);
	data->philos = philos;
	philos->data = data;
	return (0);
}
