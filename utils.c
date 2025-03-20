/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:29:25 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/20 12:44:34 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	size_t		i;
	int			sign;
	uint64_t	nb;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (sign * nb);
}

int	ft_get_time(t_sim **sim)
{
	int	time;

	gettimeofday(&(*sim)->tv, NULL);
	time = ((*sim)->tv.tv_sec * 1000) + ((*sim)->tv.tv_usec / 1000)
		- (*sim)->start_time;
	return (time);
}

void	ft_usleep(t_sim **sim, uint64_t time)
{
	uint64_t	last;

	last = ft_get_time(sim) + time;
	while (ft_get_time(sim) < last)
		usleep(100);
}
