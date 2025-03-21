/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:03:22 by tursescu          #+#    #+#             */
/*   Updated: 2025/03/21 11:48:51 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = gettime(1) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	time_to_die = philo->data->time_to_die;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_data	*table;

	table = (t_data *)data;
	while (!sim_finished(table))
	{
		i = -1;
		while (++i < table->philo_nb && !sim_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->data_mutex, &table->end_simulation, true);
				write_status(DIED, table->philos + i);
			}
		}
	}
	return (NULL);
}

/*
20) check if philo is actually full
25) extra safety margin... only a genuine miss of the eating 
	time limit will trigger death, not a 1 ms hickup;
*/