/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:47:17 by tursescu          #+#    #+#             */
/*   Updated: 2024/11/11 15:52:30 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

long	ft_atol(char *str)
{
	long	n;
	long	i;
	int		sign;

	n = 0;
	i = 0;
	sign = 1;
	if (str[i] == '0' || is_space(str[i]))
		return (-1);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		n = n * 10 + (str[i] - '0');
		i++;
	}
	if (n > INT_MAX || (n * sign) <= 0)
		return (-1);
	return (n * sign);
}

long	gettime(int time_code)
{
	static struct timeval	start;
	static pthread_mutex_t	start_mutex = PTHREAD_MUTEX_INITIALIZER;
	struct timeval			tv;

	(void) time_code;
	if (gettimeofday(&tv, NULL) != 0)
	{
		printf("Time error!\n");
		return (-1);
	}
	pthread_mutex_lock(&start_mutex);
	if (start.tv_sec == 0 && start.tv_usec == 0)
		start = tv;
	pthread_mutex_unlock(&start_mutex);
	return (((tv.tv_sec - start.tv_sec) * 1e3)
		+ ((tv.tv_usec - start.tv_usec) / 1e3));
}

void	better_usleep(long msec, t_data *data)
{
	long	start;
	long	elapsed;

	start = gettime(1);
	elapsed = start;
	while ((elapsed - start) < msec)
	{
		if (sim_finished(data))
			break ;
		if (msec - (elapsed - start) > 10)
			usleep((msec - (elapsed - start)) * 500);
		elapsed = gettime(1);
	}
}

void	clean(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < data->philo_nb)
	{
		philo = data->philos + i;
		pthread_mutex_destroy(&philo->philo_mutex);
	}
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->data_mutex);
	free(data->forks);
	free(data->philos);
}
