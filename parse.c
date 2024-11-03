/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:26:34 by mac               #+#    #+#             */
/*   Updated: 2024/11/03 08:59:13 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo * * * * [*]
//no_philo die eat sleep must_eat

#include <stdbool.h>

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||
			c == '\v' || c == '\f' || c == '\r');
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void parse_args(char **argv, t_table *table)
{
	table->philo_nbr = ft_aftol(argv[1]);
	table->time_to_die = ft_aftol(argv[2]) * 1000;
	table->time_to_eat = ft_aftol(argv[3]) * 1000;
	table->time_to_sleep = ft_aftol(argv[4]) * 1000;
	if (table->time_to_die < 60000
		|| table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
	{
		printf(RED"wrong input. time less than 60 secs\n"RST);
		clean_dinner(table);
	}
	if(argv[5])
		table->must_eat = ft_aftol(argv[5]);
	else
		table->must_eat = -1;
}

long ft_aftol(char *arg)
{
	long ret = 0;
	int i = 0;
	
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '+')
		i++;
	else if (arg[i] == '-')
		return 0;
	while (ft_isdigit(arg[i]))
	{
		ret = ret * 10 + (arg[i] - '0');
		i++;
	}
	return ret;
}
