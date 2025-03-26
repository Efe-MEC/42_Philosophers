/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:12:25 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/25 21:17:45 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_all_philos_full(t_sim *sim, int nr_philos)
{
	int	full;

	if (!ft_mtx_actions(&sim->mtx_full_philos, LOCK, sim))
		return (0);
	full = 0;
	if (sim->full_philos == nr_philos)
		full = 1;
	if (!ft_mtx_actions(&sim->mtx_full_philos, UNLOCK, sim))
		return (0);
	return (full);
}

static int	ft_death(t_sim *sim, t_philo *philo)
{
	if (!ft_mtx_actions(&philo->mtx_last_meal, UNLOCK, sim)
		|| !ft_mtx_actions(&sim->mtx_stop_sim, LOCK, sim)
		|| !ft_time_of_death(philo))
		return (0);
	sim->stop_sim = 1;
	if (!ft_mtx_actions(&sim->mtx_stop_sim, UNLOCK, sim))
		return (0);
	(void)usleep(100);
	if (!ft_print_actions(philo->timestamp_death, philo, DIE, 0))
		return (0);
	return (1);
}

static int	ft_check_die(t_sim *sim, t_philo *philo, t_ull now, t_ull t_die)
{
	if (!ft_mtx_actions(&philo->mtx_last_meal, LOCK, sim))
		return (0);
	if (now - philo->t_last_meal > t_die)
		return (ft_death(sim, philo));
	if (!ft_mtx_actions(&philo->mtx_last_meal, UNLOCK, sim))
		return (0);
	return (0);
}

void	*ft_monitor(void *arg)
{
	t_sim	*sim;
	t_ull	t_die;
	int		i;
	int		nr_philos;
	t_ull	now;

	sim = (t_sim *)arg;
	t_die = sim->t_die;
	nr_philos = sim->nr_philo;
	while (1)
	{
		if (ft_is_all_philos_full(sim, nr_philos) == 1)
			return (NULL);
		i = 0;
		now = ft_get_time();
		while (i < nr_philos)
		{
			if (ft_check_die(sim, &sim->philos[i], now, t_die) == 1)
				return (NULL);
			i++;
		}
		(void)usleep(100);
	}
	return (NULL);
}
