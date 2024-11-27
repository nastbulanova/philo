/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:12:20 by akitsenk          #+#    #+#             */
/*   Updated: 2024/11/21 09:12:21 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_data_mutex_init(t_philo_data **data)
{
	int	i;
	int	count;

	count = (*data)->philos_count;
	(*data)->philo_mutex = malloc(sizeof(pthread_mutex_t) * count);
	if (!(*data)->philo_mutex)
		error_message(*data, "Malloc error\n");
	i = 0;
	while (i < (*data)->philos_count)
	{
		if (pthread_mutex_init(&(*data)->philo_mutex[i], NULL) != 0)
		{
			(*data)->philom_count = i;
			error_message(*data, "Mutex error\n");
		}
		i++;
	}
	(*data)->philom_count = i;
}

void	forks_mutex_init(t_philo_data **data)
{
	int	i;
	int	count;

	count = (*data)->philos_count;
	(*data)->forks_mutex = malloc(sizeof(pthread_mutex_t) * count);
	if (!(*data)->forks_mutex)
		error_message(*data, "Malloc error\n");
	i = 0;
	while (i < (*data)->philos_count)
	{
		if (pthread_mutex_init(&(*data)->forks_mutex[i], NULL) != 0)
		{
			(*data)->forksm_count = i;
			error_message(*data, "Mutex error\n");
		}
		i++;
	}
	(*data)->forksm_count = i;
}
