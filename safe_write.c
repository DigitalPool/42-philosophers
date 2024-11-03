/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 06:45:03 by mac               #+#    #+#             */
/*   Updated: 2024/11/03 06:47:05 by mac              ###   ########.fr       */
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

void monitor_philos(t_table *table, int philo_id)
{
	pthread_mutex_lock(&table->table_mutex);
	table->philos[philo_id - 1].new_meal
		= gettime(MILLISECOND) - table->philos->born_time;
	if ((table->philos[philo_id - 1].new_meal
		- table->philos[philo_id - 1].time_since_last_meal)
			> table->time_to_die/1000)
	{
		printf(GREEN"%d died\n"RST, table->philos[philo_id - 1].philo_id);
		table->simulation_running = false;
		exit (0);
	}
	table->philos[philo_id - 1].time_since_last_meal
		= table->philos[philo_id - 1].new_meal;
	pthread_mutex_unlock(&table->table_mutex);
}

void	clean_dinner(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->philos[i].philo_mutex);
		pthread_mutex_destroy(&table->forks[i].fork_mutex);
	}
	pthread_mutex_destroy(&table->table_mutex);
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->must_eat_mutex);
}
