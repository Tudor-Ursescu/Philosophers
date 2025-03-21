/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tursescu <tursescu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:29:27 by tursescu          #+#    #+#             */
/*   Updated: 2025/03/21 11:48:21 by tursescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (printf("Wrong ammount of arguments.\n"), 1);
	if (parse_input(&data, av, ac) == false)
		return (printf("Wrong input!\n"), 1);
	data_init(&data);
	start_dinner(&data);
	clean(&data);
	return (0);
}

bool	parse_input(t_data *data, char **av, int ac)
{
	data->philo_nb = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		data->limit_meal = ft_atol(av[5]);
	else
		data->limit_meal = INT_MAX;
	if (data->time_to_die == -1 || data->philo_nb == -1 || data->time_to_eat
		== -1 || data->time_to_sleep == -1)
		return (false);
	if (av[5])
		if (data->limit_meal == -1)
			return (false);
	return (true);
}
