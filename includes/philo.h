/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:12:56 by tursescu          #+#    #+#             */
/*   Updated: 2024/11/11 11:32:55 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <string.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_data	t_data;

//PHILO STATUS
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

typedef enum e_time_code
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}	t_time_status;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	int			id;
	bool		full;
	long		meal_counter;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_data		*data;
	t_mtx		philo_mutex;
}	t_philo;

typedef struct s_data
{
	long		philo_nb;
	long		time_to_sleep;
	long		time_to_eat;
	long		time_to_die;
	long		limit_meal;
	long		start_simulation;
	bool		end_simulation;
	bool		all_threads_ready;
	t_fork		*forks;
	t_philo		*philos;
	t_mtx		data_mutex;
	t_mtx		write_mutex;
	pthread_t	monitor;
	long		threads_running_nb;
}	t_data;

//PARSE
bool	parse_input(t_data *data, char **av, int ac);
//INIT
bool	data_init(t_data *data);
void	philo_init(t_data *data);
void	assign_forks(t_philo *philo, t_fork *forks, int philo_pos);
//UTILS
long	gettime(int time_code);
long	ft_atol(char *str);
void	better_usleep(long msec, t_data *data);
void	clean(t_data *data);
//DINNER
void	start_dinner(t_data *data);
void	*philo_routine(t_philo *philo);
void	*lone_philo(void *arg);
//FAIRNESS
void	thinking(t_philo *philo, bool pre_simulation);
//GETTERS_SETTERS
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long	*value);
bool	sim_finished(t_data *data);
//SYNC_UTILS
void	*ft_philo(void *arg);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nb);
//WRITE_STATUS
void	write_status(t_philo_status status, t_philo *philo);
//MONITORING
void	*monitor_dinner(void *data);
#endif