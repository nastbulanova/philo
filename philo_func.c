/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:12:36 by akitsenk          #+#    #+#             */
/*   Updated: 2024/11/25 11:26:31 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_to_stop(t_philo *philo)
{
	int	stop;

	stop = 0;
	pthread_mutex_lock(philo->philomtx);
	stop = philo->stop;
	pthread_mutex_unlock(philo->philomtx);
	return (stop);
}

static void	try_to_eat(pthread_mutex_t *first, pthread_mutex_t *second,
	t_philo *philo)
{
	pthread_mutex_lock(first);
	ft_print("has taken a fork", philo);
	pthread_mutex_lock(second);
	ft_print("has taken a fork", philo);
	set_long(philo->philomtx, &(philo->last_meal), ft_get_time());
	ft_print("is eating", philo);
	ft_sleep(philo->time_to_eat);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
}

void	time_to_sleep(t_philo *philo)
{
	ft_print("is sleeping", philo);
	ft_sleep(philo->time_to_sleep);
}

void	time_to_think(t_philo *philo)
{
	ft_print("is thinking", philo);
	if ((philo->data->philos_count & 1))
		ft_sleep((philo->time_to_die - philo->time_to_eat - \
		philo->time_to_sleep) * 0.42);
}

void	*philo_go(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!(philo->num & 1))
		ft_sleep(60);
	while (!time_to_stop(philo))
	{
		if (philo->num & 1)
			try_to_eat(philo->left, philo->right, philo);
		else
			try_to_eat(philo->right, philo->left, philo);
		set_meal(philo->philomtx, &(philo->had_meals));
		time_to_sleep(philo);
		time_to_think(philo);
	}
	return (NULL);
}
