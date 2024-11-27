/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:12:46 by akitsenk          #+#    #+#             */
/*   Updated: 2024/11/21 15:38:14 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_get_time(void)
{
	struct timeval	time;

	time.tv_sec = 0;
	time.tv_usec = 0;
	gettimeofday(&time, NULL);
	return ((long long)time.tv_sec * 1000 + (long long)time.tv_usec * 0.001);
}

void	ft_sleep(int time)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	while ((now.tv_sec - start.tv_sec) * 1000 + \
		(now.tv_usec - start.tv_usec) * 0.001 < time)
	{
		usleep(50);
		gettimeofday(&now, NULL);
	}
}
