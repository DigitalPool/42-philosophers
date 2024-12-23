/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:43:26 by mac               #+#    #+#             */
/*   Updated: 2024/11/03 08:40:03 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo * * * * [*]
//no_philo die eat sleep must_eat

int	main (int argc, char **argv)
{
	t_table table;

	if (argc == 5 || argc == 6)
	{
		parse_args(argv, &table);
		table_init(&table);
		dinner_start(&table);
		clean_dinner(&table);
	}
	else
	{
		printf (RED"wrong input. usage:./philo * * * * [*]\n"RST);
		return (1);
	}
}
