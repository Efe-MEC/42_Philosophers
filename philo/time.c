/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:54:17 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/25 20:49:37 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_time(void)
{
	struct timeval	tv;
	t_ull			ms_time;

	if (gettimeofday(&tv, NULL))
	{
		ft_exiterr("Error: Could not get the time\n", NULL);
		return (0);
	}
	ms_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms_time);
}

int	ft_set_begining_time(t_sim *sim)
{
	t_ull	start_time;
	int		i;

	start_time = ft_get_time();
	if (start_time == 0)
		return (0);
	sim->t_start_sim = start_time;
	i = 0;
	while (i < sim->nr_philo)
	{
		sim->philos[i].t_last_meal = start_time;
		i++;
	}
	return (1);
}

int	ft_time_of_death(t_philo *philo)
{
	t_ull	time;

	time = ft_get_time();
	if (time == 0)
		return (0);
	philo->timestamp_death = time - philo->sim->t_start_sim;
	return (1);
}

int	ft_wait(t_ull wait_time)
{
	t_ull	stop_time;
	t_ull	now;

	stop_time = ft_get_time();
	if (stop_time == 0)
		return (0);
	stop_time += wait_time;
	while (1)
	{
		now = ft_get_time();
		if (now == 0)
			return (0);
		if (now >= stop_time)
			break ;
		(void)usleep((wait_time * 1000) / 100000);
	}
	return (1);
}
