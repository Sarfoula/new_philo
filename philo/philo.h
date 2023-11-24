/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:05:58 by yallo             #+#    #+#             */
/*   Updated: 2023/11/24 16:40:51 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				fork;
	int				*next_fork;
	int				meal_eaten;
	size_t			last_meal;
	int				*dead_flag;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*m_eating;
	pthread_mutex_t	*m_fork;
	pthread_mutex_t	*m_next_fork;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				dead_flag;
	int				nbr_philo;
	int				must_eat;
	size_t			start_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_mutex_t	dead;
	pthread_mutex_t	eating;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}				t_data;

//Parse
int		check_args(int argc, char **argv);

//Init
int		init(t_data *data, char **argv);

//Forks
int		take_fork(t_philo *philo, pthread_mutex_t *m_fork, int *fork);
void	free_forks(t_philo *philo);

//Routine
void	*routine(void *pointer);

//Monitoring
int		monitoring(t_data *data);

//Threads
int		create_threads(t_data *data);
int		join_threads(t_data *data);

//Utils
long	ft_atoi(const char *str);
size_t	get_time(void);
int		ft_prompt(t_philo *philo, char *display);
void	ft_usleep(size_t time, t_philo *philo);
void	free_all(t_data *data, t_philo *philo, int mutex, char *display);

#endif
