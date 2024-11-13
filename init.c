/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:59:58 by tursescu          #+#    #+#             */
/*   Updated: 2024/11/11 11:33:05 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	data_init(t_data *data)
{
	int	i;

	i = -1;
	data->end_simulation = false;
	data->all_threads_ready = false;
	data->threads_running_nb = 0;
	data->forks = malloc(sizeof(t_fork) * data->philo_nb);
	data->philos = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->forks || !data->philos)
		return (printf("Malloc error\n"), false);
	pthread_mutex_init(&data->data_mutex, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	while (++i < data->philo_nb)
	{
		pthread_mutex_init(&data->forks[i].fork, NULL);
		data->forks->fork_id = i;
	}
	philo_init(data);
	return (true);
}

void	philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->philo_nb)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meal_counter = 0;
		philo->data = data;
		philo->last_meal_time = gettime(MILISECOND);
		pthread_mutex_init(&philo->philo_mutex, NULL);
		assign_forks(philo, data->forks, i);
	}
}

void	assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	philo_nb;

	philo_nb = philo->data->philo_nb;
	philo->first_fork = &forks[(philo_pos + 1) % philo_nb];
	philo->second_fork = &forks[philo_pos];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % philo_nb];
	}
}
