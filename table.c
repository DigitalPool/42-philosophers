/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:14:17 by mac               #+#    #+#             */
/*   Updated: 2024/11/01 03:56:11 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	is_philo_full(t_philos *philo)
{
	if (philo->table->philos[philo->philo_id - 1].meals_counter == philo->table->must_eat)
	{
		pthread_mutex_lock(&philo->table->must_eat_mutex);
		philo->table->full_philos_count++;
		if (philo->table->full_philos_count == philo->table->philo_nbr)
			philo->table->simulation_running = false;
		pthread_mutex_unlock(&philo->table->must_eat_mutex);
	}
}

static void	eat_sleep_think(t_philos *philo, int current_time)
{
		int right_fork_index = philo->philo_id - 1;
		int left_fork_index = (philo->philo_id) % philo->table->philo_nbr;
		current_time = gettime(MILLISECOND);
		pthread_mutex_lock(&philo->table->forks[right_fork_index].fork_mutex);
		monitor_philos(philo->table, philo->philo_id);
		safe_write(philo->table, "has taken right fork", philo->philo_id);
		pthread_mutex_lock(&philo->table->forks[left_fork_index].fork_mutex);
		safe_write(philo->table, "has taken left fork", philo->philo_id);
		pthread_mutex_lock(&philo->table->table_mutex);
		safe_write(philo->table, "is eating", philo->philo_id);
		philo->table->philos[philo->philo_id - 1].meals_counter++;
		is_philo_full(philo);
		pthread_mutex_unlock(&philo->table->table_mutex);
		precise_usleep(philo->table->time_to_eat);
		pthread_mutex_unlock(&philo->table->forks[right_fork_index].fork_mutex);
		pthread_mutex_unlock(&philo->table->forks[left_fork_index].fork_mutex);
		safe_write(philo->table, "is sleeping", philo->philo_id);
		precise_usleep(philo->table->time_to_sleep);
		safe_write(philo->table, "is thinking", philo->philo_id);
		current_time = gettime(MILLISECOND);
}

void	*dinner_simulation(void *data)
{
	t_philos *philo;
	long current_time;

	philo = (t_philos *)data;
	if (philo->philo_id % 2 == 0)
		precise_usleep(200);
	pthread_mutex_lock(&philo->table->table_mutex);
	philo->born_time = gettime(MILLISECOND);
	pthread_mutex_unlock(&philo->table->table_mutex);
	while (philo->table->simulation_running)
		eat_sleep_think(philo, current_time);
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int i;
	int j;

	i = -1;
	j = -1;
	if (table->philo_nbr == 1)
	{
		printf(GREEN"%d"RST	"	1 has taken a fork\n", 0);
		printf(RED"%ld"RST	"	1 died\n", table->time_to_die/1000);
		clean_dinner(table);
	}
	else
	{
		while(++i < table->philo_nbr)
			pthread_create(&table->philos[i].thread_id, NULL, &dinner_simulation, &table->philos[i]);
		table->start_simulation = gettime(MILLISECOND);
		while (++j < table->philo_nbr)
			pthread_join(table->philos[j].thread_id, NULL);
	}
}
