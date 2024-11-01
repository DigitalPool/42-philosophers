/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 04:03:58 by mac               #+#    #+#             */
/*   Updated: 2024/11/01 04:06:15 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void			init_philos(t_table *table)
{
	int i;

	i = -1;
	table->simulation_running = true;
	table->full_philos_count = 0;
	pthread_mutex_init(&table->table_mutex, NULL);
	pthread_mutex_init(&table->write_mutex, NULL);
	pthread_mutex_init(&table->must_eat_mutex, NULL);
	table->forks = malloc(sizeof(t_forks) * table->philo_nbr);
	if (!table->forks)
		exit(0);
	table->philos = malloc(sizeof(t_philos) * table->philo_nbr);
	if (!table->philos)
		exit(0);
	while (++i < table->philo_nbr)
	{
		pthread_mutex_init(&table->forks[i].fork_mutex, NULL);
		table->forks[i].fork_id = i + 1;
	}
}
void			init_mutexes(t_table *table)
{
	int j;

	j = -1;
	while (++j < table->philo_nbr)
	{
		pthread_mutex_init(&table->philos[j].philo_mutex, NULL);
		table->philos[j].philo_id = j + 1;
		table->philos[j].philo_right_fork = table->forks[j];
		table->philos[j].philo_left_fork = table->forks[(j + 1) % table->philo_nbr];
		table->philos[j].time_since_last_meal = gettime(MILLISECOND);
		table->philos[j].new_meal = gettime(MILLISECOND);//
		table->philos[j].born_time = gettime(MILLISECOND);
		table->philos[j].time_has_slept = 0;
		table->philos[j].meals_counter = 0;
		table->philos[j].table = table;
	}
}


void table_init(t_table *table)
{
	init_philos(table);
	init_mutexes(table);
}
