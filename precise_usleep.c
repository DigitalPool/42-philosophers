/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precise_usleep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:42:12 by mac               #+#    #+#             */
/*   Updated: 2024/11/03 06:48:59 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long gettime(t_time_code time_code)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		printf(RED"error with gettimeofday\n"RST);
		exit(1);
	}
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	else
	{
		printf(RED"wrong input to get time of day\n"RST);
		exit(1);
	}
	return (1337);
}

void	precise_usleep(long usec)
{
	long start;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
		usleep(500);
}

void	take_time_doing(long unsigned int time_to_take)
{
	unsigned int	start;
	unsigned int	current;

	start = gettime(MILLISECOND);
	current = start;
	while (current < start + time_to_take)
	{
		usleep(100);
		current = gettime(MILLISECOND);
	}
	return ;
}

