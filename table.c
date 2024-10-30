/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:14:17 by mac               #+#    #+#             */
/*   Updated: 2024/10/30 16:35:29 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void table_init(t_table *table)
{
	int i;
	int j;

	i = -1;
	j = -1;
	table->simulation_running = true;
	pthread_mutex_init(&table->table_mutex, NULL);
	pthread_mutex_init(&table->write_mutex, NULL);
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
		printf("forks %d\n", table->forks[i].fork_id);
	}

	while (++j < table->philo_nbr)
	{
		pthread_mutex_init(&table->philos[j].philo_mutex, NULL);
		table->philos[j].philo_id = j + 1;

		printf("philos %d\n", table->philos[j].philo_id);

		table->philos[j].philo_right_fork = table->forks[j];
		table->philos[j].philo_left_fork = table->forks[(j + 1) % table->philo_nbr];
		table->philos[j].time_since_last_meal = gettime(MILLISECOND);
		table->philos[j].time_has_slept = 0;
		table->philos[j].meals_counter = 0;
		// table->philos[j].thread_id = j;
		table->philos[j].table = table;
	}
}

void dinner_start(t_table *table)
{
	int i;
	int j;

	i = -1;
	j = -1;
	if (table->philo_nbr == 1)
		{
			// handle_one_philo()
			printf("%d	", 0);
			safe_write(table, "has taken right fork", table->philos->philo_id);
			printf("%ld	", table->time_to_die/1000);
			safe_write(table, "is dead", table->philos->philo_id);
			//clean table //TODO
			exit(0);
		}
	else
	{
		//create thread for all
		while(++i < table->philo_nbr)
			pthread_create(&table->philos[i].thread_id, NULL, &dinner_simulation, &table->philos[i]);

		//record the time when the threead was created started
		table->start_simulation = gettime(MILLISECOND);

		while (++j < table->philo_nbr)
			pthread_join(table->philos[j].thread_id, NULL);
	}
}


void	*dinner_simulation(void *data)
{
 	int right_fork_index;
	int left_fork_index;

	t_philos *philo;

	philo = (t_philos *)data;

	if (philo->philo_id % 2 == 0)
		precise_usleep(200);

	//dpetrosy
	pthread_mutex_lock(&philo->table->table_mutex);
	philo->born_time = gettime(MILLISECOND); // might remove
	philo->time_since_last_meal = gettime(MILLISECOND);
	pthread_mutex_unlock(&philo->table->table_mutex);
	//dpetrosy

	while (philo->table->simulation_running)
	{
		int right_fork_index = philo->philo_id - 1;
		int left_fork_index = (philo->philo_id) % philo->table->philo_nbr;

		pthread_mutex_lock(&philo->table->forks[right_fork_index].fork_mutex);
		safe_write(philo->table, "has taken right fork", philo->philo_id);
		printf("fork_id %d\n", philo->table->forks[right_fork_index].fork_id);

		pthread_mutex_lock(&philo->table->forks[left_fork_index].fork_mutex);
		safe_write(philo->table, "has taken left fork", philo->philo_id);
		printf("fork_id  %d\n", philo->table->forks[left_fork_index].fork_id);

		// pthread_mutex_lock(&philo->table->table_mutex); //meal_lock
		philo->time_since_last_meal = gettime(MILLISECOND);
		philo->meals_counter++;
		safe_write(philo->table, "is eating", philo->philo_id);
		precise_usleep(philo->table->time_to_eat);
		// if (philo->table->must_eat > 0 && philo->meals_counter >= philo->table->must_eat)
		// 	break ;
		// pthread_mutex_unlock(&philo->table->table_mutex);

		pthread_mutex_unlock(&philo->table->forks[right_fork_index].fork_mutex);
		pthread_mutex_unlock(&philo->table->forks[left_fork_index].fork_mutex);


		safe_write(philo->table, "is sleeping", philo->philo_id);
		precise_usleep(philo->table->time_to_sleep);

		// take_time_doing(philo->table, philo->table->time_to_sleep);
		safe_write(philo->table, "is thinking", philo->philo_id);
		precise_usleep(50 + (rand() % 100));

	}
	return (NULL);
}



