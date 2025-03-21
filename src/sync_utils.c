/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:13:52 by tursescu          #+#    #+#             */
/*   Updated: 2025/03/21 11:48:54 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_nb == 1)
		lone_philo(philo);
	if (philo->id % 2 == 0)
		write_status(THINKING, philo);
	philo_routine(philo);
	return (NULL);
}

bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nb)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mutex);
	if (*threads == philo_nb)
		ret = true;
	pthread_mutex_unlock(mutex);
	return (ret);
}
