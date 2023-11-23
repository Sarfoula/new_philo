/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:05:58 by yallo             #+#    #+#             */
/*   Updated: 2023/11/23 18:50:45 by yallo            ###   ########.fr       */
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
	pthread_mutex_t	*dead;
	pthread_mutex_t	*eating;
	pthread_mutex_t	*prompt;
	pthread_mutex_t	*m_fork;
	pthread_mutex_t	*m_next_fork;
	struct s_data			*data;
}			t_philo;

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
	pthread_mutex_t	prompt;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}			t_data;

//Parse
int			parse(int argc, char **argv);

//Init
int	init(t_data *data, t_philo *philos, char **argv);

//Routine
void *routine(void *pointer);

//Monitoring
void	*monitoring(t_philo *philos);

//Threads
int create_threads(t_data *data);
int join_threads(t_data *data);

//Utils
long		ft_atoi(const char *str);
long int	get_time(void);
void		free_all(t_data *data, t_philo *philos, char *display);
void		ft_prompt(t_philo *philo, char *display);
void		ft_usleep(size_t time);

#endif
