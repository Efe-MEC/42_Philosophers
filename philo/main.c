/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:38:28 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/23 17:00:50 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
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

static int	ft_start_sim(t_sim *sim)
{
	if (!ft_set_begining_time(sim))
		return (0);
	if (sim->nr_philo == 1)
	{
		if (!ft_one_philo_state(sim))
			return (0);
		return (1);
	}
	if (!ft_start_monitor(sim))
		return (0);
	if (!ft_start_dinner(sim))
		return (0);
	if (!ft_end_dinner(sim))
		return (0);
	if (!ft_end_monitor(sim))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_sim	*sim;

	sim = NULL;
	if (!ft_init_sim(&sim, argc, argv))
	{
		ft_free_sim(&sim);
		return (0);
	}
	if (!ft_start_sim(sim))
	{
		ft_free_sim(&sim);
		return (0);
	}
	ft_free_sim(&sim);
	return (0);
}
