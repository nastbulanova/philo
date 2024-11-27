/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:12:09 by akitsenk          #+#    #+#             */
/*   Updated: 2024/11/25 15:32:24 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_value(char *arg, t_philo_data *data)
{
	int	value;

	value = 0;
	value = ft_atoi_mod(arg);
	if (value == -1)
		error_message(data, "Incorrect input\n");
	return (value);
}

void	data_init(int argc, char **argv, t_philo_data *data)
{
	data->philos = NULL;
	data->stdout_m = 0;
	data->philom_count = 0;
	data->forksm_count = 0;
	data->philos_count = get_value(argv[1], data);
	if (data->philos_count == 0)
		error_message(data, "And what are you waiting for with 0 philos?\n");
	data->time_to_die = get_value(argv[2], data);
	data->time_to_eat = get_value(argv[3], data);
	data->time_to_sleep = get_value(argv[4], data);
	if (argc == 6)
		data->max_meals = get_value(argv[5], data);
	else
		data->max_meals = -1;
	forks_mutex_init(&data);
	philo_data_mutex_init(&data);
	if (pthread_mutex_init(&data->stdout_mutex, NULL) != 0)
		error_message(data, "Mutex error\n");
	else
		data->stdout_m = 1;
}

void	philos_init_val(t_philo_data **data, int i)
{
	(*data)->philos[i].id = 0;
	(*data)->philos[i].num = i + 1;
	(*data)->philos[i].time_to_die = (*data)->time_to_die;
	(*data)->philos[i].time_to_eat = (*data)->time_to_eat;
	(*data)->philos[i].time_to_sleep = (*data)->time_to_sleep;
	(*data)->philos[i].had_meals = 0;
	(*data)->philos[i].last_meal = 0;
	(*data)->philos[i].stop = 0;
	(*data)->philos[i].data = *data;
	(*data)->philos[i].start_time = 0;
}

void	philos_init(t_philo_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philos_count);
	if (!data->philos)
		error_message(data, "Malloc error\n");
	while (i < data->philos_count)
	{
		philos_init_val(&data, i);
		data->philos[i].right = &(data->forks_mutex[i]);
		data->philos[i].philomtx = &(data->philo_mutex[i]);
		if (i == 0)
			data->philos[i].left = &(data->forks_mutex[data->philos_count - 1]);
		else
			data->philos[i].left = &(data->forks_mutex[i - 1]);
		if (data->max_meals)
			data->philos[i].max_meals = data->max_meals;
		else
			data->philos[i].max_meals = -1;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo_data	*data;

	data = malloc(sizeof(t_philo_data));
	if (!data)
		return (write(1, "Malloc error\n", 13), 1);
	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments\n");
		free(data);
		return (0);
	}
	else
		data_init(argc, argv, data);
	philos_init(data);
	threads_go(data);
	if (data->philos_count == 1)
		printf("\n\nHe is dead. Are you happy now?\n");
	clean_before_exit(data);
	return (0);
}
