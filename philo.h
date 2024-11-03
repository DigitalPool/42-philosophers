/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:39:44 by mac               #+#    #+#             */
/*   Updated: 2024/11/03 08:21:21 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define	PHILO_H

#include <stdio.h> //printf
#include <unistd.h> //write
#include <stdlib.h> //malloc
#include <pthread.h> //pthreads
#include <sys/wait.h> //wait
#include <sys/time.h> //wait
#include <ctype.h> //isdigi, isspace
#include <stdbool.h> //bool

// ./philo * * * * [*]
//no_philo die eat sleep must_eat

// Reset to default color
#define RST		"\033[0m"

// Bold Colors
#define RED		"\033[1;31m"	// Bold Red
#define GREEN	"\033[1;32m"	// Bold Green
#define YELLOW	"\033[1;33m"	// Bold Yellow
#define BLUE	"\033[1;34m"	// Bold Blue
#define MAGENTA	"\033[1;35m"	// Bold Magenta
#define CYAN	"\033[1;36m"	// Bold Cyan
#define WHITE	"\033[1;37m"	// Bold White

typedef enum	e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}				t_time_code;

typedef 		pthread_mutex_t t_mtx;
typedef struct	s_table t_table;

typedef struct	s_forks
{
	int			fork_id;
	t_mtx		fork_mutex;
}				t_forks;

typedef struct	s_philos
{
	int 		philo_id;
	t_forks 	philo_right_fork;
	t_forks		philo_left_fork;
	long		time_since_last_meal;
	long		new_meal;
	long		time_has_slept;
	long		born_time;
	t_table		*table;
	int			meals_counter;
	t_mtx		philo_mutex;
	pthread_t	thread_id;
}				t_philos;

typedef struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		must_eat;
	long		start_simulation;
	bool		simulation_running;
	int			full_philos_count;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	t_mtx		must_eat_mutex;
	t_forks		*forks;
	t_philos	*philos;
}				t_table;

//parsing
long			ft_aftol(char *arg);
void			parse_args(char **argv, t_table *table);

//init
void			init_philos(t_table *table);
void			init_mutexes(t_table *table);
void			table_init(t_table *table);

//precise u_sleep
void			precise_usleep(long usec);
long			gettime(t_time_code time_code);
void	take_time_doing(long unsigned int time_to_take);

//dinner starts. why not?
void			dinner_start(t_table *table);
void			*dinner_simulation(void *data);

//safe write
void			safe_write(t_table *table, char *status, int philo_id);
void			safe_write_died(t_table *table, char *status, int philo_id);
void			monitor_philos(t_table *table, int philo_id);

// clean everything my love
void			clean_dinner(t_table *table);

#endif
