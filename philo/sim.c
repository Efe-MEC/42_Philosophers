/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:47:51 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/25 21:18:02 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_one_philo_state(t_sim *sim)
{
	int	t_die;

	t_die = sim->t_die;
	(void)printf("%d %d %s\n", 0, 1, "has taken a fork");
	if (t_die > 0)
	{
		(void)usleep(t_die * 1000);
		(void)printf("%d %d %s\n", t_die, 1, "died");
	}
	return (1);
}

int	ft_start_monitor(t_sim *sim)
{
	if (sim->max_meals == 0)
		return (1);
	if (pthread_create(&sim->monitor, NULL, &ft_monitor, sim))
	{
		ft_exiterr("Error: Thread can not generated", sim);
		return (0);
	}
	(void)usleep(100);
	return (1);
}

int	ft_end_monitor(t_sim *sim)
{
	if (sim->max_meals == 0)
		return (1);
	if (pthread_join(sim->monitor, NULL))
	{
		ft_exiterr("Error: Thread can not joined", sim);
		return (0);
	}
	return (1);
}

int	ft_start_dinner(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->nr_philo)
	{
		if (pthread_create(&sim->philos[i].thread_id, NULL, &ft_ops,
				&sim->philos[i]))
		{
			(void)ft_mtx_actions(&sim->mtx_stop_sim, LOCK, sim);
			sim->stop_sim = 1;
			(void)ft_mtx_actions(&sim->mtx_stop_sim, UNLOCK, sim);
			while (i > 0)
				pthread_join(sim->philos[--i].thread_id, NULL);
			ft_end_monitor(sim);
			(void)usleep(100);
			ft_exiterr("Error: Thread can not generated", sim);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_end_dinner(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->nr_philo)
	{
		if (pthread_join(sim->philos[i].thread_id, NULL))
		{
			ft_mtx_actions(&sim->mtx_stop_sim, LOCK, sim);
			sim->stop_sim = 1;
			ft_mtx_actions(&sim->mtx_stop_sim, UNLOCK, sim);
			ft_end_monitor(sim);
			(void)usleep(100);
			ft_exiterr("Error: Thread can not joined", sim);
			return (0);
		}
		i++;
	}
	return (1);
}
