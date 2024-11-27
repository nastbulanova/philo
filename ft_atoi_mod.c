/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_mod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:11:15 by akitsenk          #+#    #+#             */
/*   Updated: 2024/11/21 09:11:22 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	err_check(size_t len, char *str, long long nb)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i ++;
	if (len < i)
		return (1);
	if (i == 0)
		return (1);
	else if (i == 1 && nb == 0 && (str[0] == '-' || str[0] == '+'))
		return (1);
	else
		return (0);
}

int	ft_atoi_mod(char *str)
{
	size_t		i;
	long long	nb;
	int			sign;
	int			atoi_error;

	i = 0;
	sign = 1;
	nb = 0;
	atoi_error = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	atoi_error = err_check(i, str, nb);
	nb = nb * sign;
	if (nb > 2147483647 || nb < 0 || atoi_error)
		return (-1);
	return ((int)nb);
}
