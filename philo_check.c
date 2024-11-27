/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:12:30 by akitsenk          #+#    #+#             */
/*   Updated: 2024/11/25 11:38:02 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_stop_flag(t_philo_data **data)
{
	int	i;

	i = 0;
	while (i < (*data)->philos_count)
	{
		pthread_mutex_lock(&((*data)->philo_mutex[i]));
		(*data)->philos[i].stop = 1;
		pthread_mutex_unlock(&((*data)->philo_mutex[i]));
		i++;
	}
}

int	is_dead(t_philo_data *data, t_philo *philo)
{
	long long	last_meal;

	last_meal = 0;
	last_meal = get_long(philo->philomtx, &(philo->last_meal));
	if (last_meal != 0)
	{
		if (ft_get_time() - last_meal >= data->time_to_die)
			return (1);
	}
	else
	{
		if (ft_get_time() - data->start_time >= data->time_to_die)
			return (1);
	}
	return (0);
}

static int	someone_died(t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		if (is_dead(data, &(data->philos[i])))
		{
			ft_print("died", &(data->philos[i]));
			set_stop_flag(&data);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	reach_max_meals(t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		if (get_int(&(data->philo_mutex[i]),
				&(data->philos[i].had_meals)) < data->max_meals)
			return (0);
		i++;
	}
	set_stop_flag(&data);
	pthread_mutex_lock(&data->stdout_mutex);
	printf("%lld all the philos are full\n",
		ft_get_time() - data->start_time);
	pthread_mutex_unlock(&data->stdout_mutex);
	return (1);
}

void	*philo_check(void *arg)
{
	t_philo_data	*data;
	int				corpse;
	int				are_full;

	data = (t_philo_data *)arg;
	corpse = 0;
	are_full = 0;
	while (1)
	{
		if (data->max_meals > -1)
			are_full = reach_max_meals(data);
		corpse = someone_died(data);
		if (are_full || corpse)
			break ;
	}
	return (NULL);
}
