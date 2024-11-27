/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:12:26 by akitsenk          #+#    #+#             */
/*   Updated: 2024/11/21 14:57:17 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(char *message, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->stdout_mutex);
	if (!time_to_stop(philo))
		printf("%lld %d %s\n", ft_get_time() - philo->data->start_time,
			philo->num, message);
	pthread_mutex_unlock(&philo->data->stdout_mutex);
}

int	get_int(pthread_mutex_t *mutex, int *from)
{
	int	value;

	value = 0;
	pthread_mutex_lock(mutex);
	value = *from;
	pthread_mutex_unlock(mutex);
	return (value);
}

void	set_int(pthread_mutex_t *mutex, int *where, int value)
{
	pthread_mutex_lock(mutex);
	*where = value;
	pthread_mutex_unlock(mutex);
}

long long	get_long(pthread_mutex_t *mutex, long long *from)
{
	long long	value;

	value = 0;
	pthread_mutex_lock(mutex);
	value = *from;
	pthread_mutex_unlock(mutex);
	return (value);
}

void	set_long(pthread_mutex_t *mutex, long long *where, long long value)
{
	pthread_mutex_lock(mutex);
	*where = value;
	pthread_mutex_unlock(mutex);
}

// --tool=helgrind --tool=rdr
