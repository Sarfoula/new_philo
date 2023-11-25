/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:04:12 by yallo             #+#    #+#             */
/*   Updated: 2023/11/25 16:36:42 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_data			*data;

	if (argc != 5 && argc != 6)
		return (write(2, "Error: Wrong number of arguments\n", 33), 0);
	if (check_args(argc, argv) == 1)
		return (0);
	data = malloc(sizeof(t_data));
	if (!data)
		return (write(2, "Error: malloc failed\n", 22), 0);
	if (init(data, argv) == 1)
		return (0);
	create_threads(data);
	monitoring(data);
	join_threads(data);
	free_all(data, data->philos, 1, NULL);
	return (0);
}
