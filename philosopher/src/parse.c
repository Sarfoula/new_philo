/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yallo <yallo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:06:11 by yallo             #+#    #+#             */
/*   Updated: 2023/11/24 05:28:15 by yallo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	check_str(char *str, int idx)
{
	long	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' && str[i] > '9')
			return (1);
		if (i > 11)
			return (write(2, "Error: integers has limits\n", 27), 1);
		i++;
	}
	i = ft_atoi(str);
	if (i <= 0)
		return (write(2, "Error: argument not valid\n", 26), 1);
	if (i > 2147483647)
		return (write(2, "Error: integers has limits\n", 27), 1);
	if (i > 200 && idx == 1)
		return(write(2, "Error: maximum 200 philos\n", 26), 1);
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (write(2, "Error: argument can only be integers\n", 37), 1);
			j++;
		}
		if (check_str(argv[i], i) == 1)
			return (1);
		i++;
	}
	return (0);
}
