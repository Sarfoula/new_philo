/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:12:50 by yallo             #+#    #+#             */
/*   Updated: 2023/11/24 16:37:40 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->eating, NULL);
	pthread_mutex_init(&data->dead, NULL);
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	init_data(t_data *data, char **argv)
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

void	init_philos(t_philo *philos, t_data *data, char **argv)
{
	int	nbr_philo;
	int	i;

	data->philos = philos;
	i = 0;
	nbr_philo = ft_atoi(argv[1]);
	while (i < nbr_philo)
	{
		philos[i].m_eating = &data->eating;
		philos[i].dead_flag = &data->dead_flag;
		philos[i].id = i + 1;
		philos[i].fork = 1;
		philos[i].m_fork = &data->forks[i];
		philos[i].next_fork = &philos[(i + 1) % nbr_philo].fork;
		philos[i].m_next_fork = &data->forks[(i + 1) % nbr_philo];
		philos[i].meal_eaten = 0;
		philos[i].dead = &data->dead;
		philos[i].data = data;
		i++;
	}
}

int	init(t_data *data, char **argv)
{
	pthread_mutex_t	*fork;
	t_philo			*philo;

	init_data(data, argv);
	philo = malloc(sizeof(t_philo) * data->nbr_philo);
	if (!philo)
		return (free_all(data, NULL, 0, "Error: malloc failed\n"), 1);
	fork = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	if (!fork)
		return (free_all(data, NULL, 0, "Error: malloc failed\n"), 1);
	data->philos = philo;
	data->forks = fork;
	init_mutex(data);
	init_philos(philo, data, argv);
	return (0);
}
