/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_error_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:11:27 by akitsenk          #+#    #+#             */
/*   Updated: 2024/11/21 09:11:28 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_message(t_philo_data *data, char *message)
{
	printf("%s", message);
	clean_before_exit(data);
}

void	forks_mutex_destroy(t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < data->forksm_count)
	{
		pthread_mutex_destroy(&(data->forks_mutex[i]));
		i++;
	}
	free(data->forks_mutex);
}

void	philo_mutex_destroy(t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < data->philom_count)
	{
		pthread_mutex_destroy(&(data->philo_mutex[i]));
		i++;
	}
	free(data->philo_mutex);
}

void	clean_before_exit(t_philo_data *data)
{
	if (data)
	{
		if (data->forksm_count)
			forks_mutex_destroy(data);
		if (data->philom_count)
			philo_mutex_destroy(data);
		if (data->stdout_m)
			pthread_mutex_destroy(&data->stdout_mutex);
		if (data->philos)
			free(data->philos);
		free(data);
		data = NULL;
	}
	exit(0);
}
