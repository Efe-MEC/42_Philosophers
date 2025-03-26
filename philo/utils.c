/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 23:22:35 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/26 23:23:05 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_value_overflow(const char *token)
{
	int	sign;
	int	value;
	int	digit;

	sign = 1;
	value = 0;
	if (*token == '-')
	{
		sign = -1;
		token++;
	}
	else if (*token == '+')
		token++;
	while (*token >= '0' && *token <= '9')
	{
		digit = *token - '0';
		if ((sign == 1 && (value > INT_MAX / 10
					|| (value == INT_MAX / 10 && digit > INT_MAX % 10)))
			|| (sign == -1 && (value > -(INT_MIN / 10)
					|| (value == -(INT_MIN / 10) && digit > -(INT_MIN % 10)))))
			return (1);
		value = value * 10 + digit;
		token++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	if (ft_is_value_overflow(str))
		return (-1);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = sign * -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * sign);
}
