/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treads_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:12:51 by akitsenk          #+#    #+#             */
/*   Updated: 2024/11/25 11:41:56 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_will_die(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_long(philo->philomtx, &(philo->start_time), ft_get_time());
	while (1)
	{
		if (time_to_stop(philo))
			break ;
		pthread_mutex_lock(philo->right);
		ft_print("has taken a fork", philo);
		pthread_mutex_unlock(philo->right);
		time_to_sleep(philo);
		ft_print("is thinking", philo);
	}
	return (NULL);
}

void	only_one_hungry_guy(t_philo_data *data)
{
	printf("We don't need to start, he will die anyway.\n");
	ft_sleep(2000);
	printf("Are you really want to see this?\n");
	ft_sleep(3000);
	printf("That's weird. But okay, let's start...\n\n\n");
	ft_sleep(3000);
	data->start_time = ft_get_time();
	if (pthread_create(&(data->philos[0].id), NULL, &philo_will_die,
			(void *)&data->philos[0]) != 0)
		error_message(data, "Creating treads error");
}

void	threads_abort(t_philo_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		data->philos[i].stop = 1;
		i++;
	}
	i = 0;
	while (i < count)
	{
		pthread_join(data->philos[i].id, NULL);
		i ++;
	}
	error_message(data, "Creating treads error");
}

void	threads_go(t_philo_data *data)
{
	int	i;

	i = 0;
	if (data->philos_count == 1)
		only_one_hungry_guy(data);
	else
	{
		data->start_time = ft_get_time();
		while (i < data->philos_count)
		{
			if (pthread_create(&(data->philos[i].id), NULL, &philo_go,
					(void *)&data->philos[i]) != 0)
				threads_abort(data, i);
			i ++;
		}
	}
	if (pthread_create(&(data->check_philos), NULL, &philo_check,
			(void *)data) != 0)
		threads_abort(data, data->philos_count);
	i = -1;
	while (++i < data->philos_count)
		pthread_join(data->philos[i].id, NULL);
	pthread_join(data->check_philos, NULL);
}
