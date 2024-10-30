/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 06:45:03 by mac               #+#    #+#             */
/*   Updated: 2024/10/30 19:07:00 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void safe_write(t_table *table, char *status, int philo_id)
{
	long time_taken;

	pthread_mutex_lock(&table->write_mutex);
	time_taken = gettime(MILLISECOND) - table->philos->born_time;
	printf(GREEN"%ld "RST"%d %s\n", time_taken, philo_id, status);
	pthread_mutex_unlock(&table->write_mutex);
}

void safe_write_died(t_table *table, char *status, int philo_id)
{
	long time_taken;

	pthread_mutex_lock(&table->write_mutex);
	time_taken = gettime(MILLISECOND) - table->philos->born_time;
	printf(RED"%ld "RST"%d %s\n", time_taken, philo_id, status);
	pthread_mutex_unlock(&table->write_mutex);
}