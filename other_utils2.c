/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:13:30 by akitsenk          #+#    #+#             */
/*   Updated: 2024/11/21 09:13:31 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_meal(pthread_mutex_t *mutex, int *where)
{
	pthread_mutex_lock(mutex);
	*where = *where + 1;
	pthread_mutex_unlock(mutex);
}
