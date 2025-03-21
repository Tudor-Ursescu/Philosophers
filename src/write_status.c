/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:25:35 by tursescu          #+#    #+#             */
/*   Updated: 2025/03/21 11:48:58 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime(1);
	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->data->write_mutex);
	if ((!sim_finished(philo->data))
		&& (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK))
		printf("%ld  %d has taken a fork\n", elapsed, philo->id);
	else if (status == EATING && !sim_finished(philo->data))
		printf("%ld  %d is eating\n", elapsed, philo->id);
	else if (status == SLEEPING && !sim_finished(philo->data))
		printf("%ld  %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !sim_finished(philo->data))
		printf("%ld  %d is thinking\n", elapsed, philo->id);
	else if (status == DIED && sim_finished(philo->data))
		printf("%ld  %d is dead\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->data->write_mutex);
}
