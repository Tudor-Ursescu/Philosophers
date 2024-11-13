/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:38:21 by tursescu          #+#    #+#             */
/*   Updated: 2024/11/11 16:01:56 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(1));
	write_status(TAKE_FIRST_FORK, philo);
	while (!sim_finished(philo->data))
		usleep(100);
	return (NULL);
}

void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		write_status(THINKING, philo);
	if (philo->data->philo_nb % 2 == 0)
		return ;
	t_eat = philo->data->time_to_eat;
	t_sleep = philo->data->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	better_usleep(t_think, philo->data);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	write_status(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(1));
	philo->meal_counter++;
	write_status(EATING, philo);
	better_usleep(philo->data->time_to_eat, philo->data);
	if (philo->data->limit_meal > 0
		&& philo->meal_counter == philo->data->limit_meal)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	*philo_routine(t_philo *philo)
{
	while (!sim_finished(philo->data))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		better_usleep(philo->data->time_to_sleep, philo->data);
		thinking(philo, false);
	}
	return (NULL);
}

void	start_dinner(t_data *data)
{
	int	i;

	i = -1;
	if (data->limit_meal == 0)
		return ;
	else if (data->philo_nb == 1)
		pthread_create(&data->philos[0].thread_id, NULL, ft_philo,
			&data->philos[0]);
	else
		while (++i < data->philo_nb)
			pthread_create(&data->philos[i].thread_id, NULL, ft_philo,
				&data->philos[i]);
	pthread_create(&data->monitor, NULL, monitor_dinner, data);
	data->start_simulation = gettime(1);
	set_bool(&data->data_mutex, &data->all_threads_ready, true);
	i = -1;
	while (++i < data->philo_nb)
		pthread_join(data->philos[i].thread_id, NULL);
	set_bool(&data->data_mutex, &data->end_simulation, true);
	pthread_join(data->monitor, NULL);
}

/*
35) if even, just return (system is fair)
37) if odd, could be unfair
47) fork assignment phase
51) eating phase
58) let go of the forks phase
90) create monitor that handles death function
91) begin simulation
92) declare all threads as ready
96) at this point, all philos are full, so we need to stop the sim
*/