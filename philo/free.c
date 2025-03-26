/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:39:59 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/22 20:57:55 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_free_philos(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->nr_philo)
	{
		if (sim->philos[i].mtx_last_meal_init)
			(void)ft_mtx_actions(&sim->philos[i].mtx_last_meal, DESTROY, sim);
		i++;
	}
	free(sim->philos);
	sim->philos = NULL;
}

static void	ft_free_forks(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->nr_philo)
	{
		(void)ft_mtx_actions(&sim->forks[i].fork, DESTROY, sim);
		i++;
	}
	free(sim->forks);
	sim->forks = NULL;
}

void	ft_free_sim(t_sim **sim)
{
	t_sim	*tmp;

	tmp = *sim;
	if (!tmp)
		return ;
	if (tmp->forks)
		ft_free_forks(tmp);
	if (tmp->philos)
		ft_free_philos(tmp);
	if (tmp->mtx_full_philos_init)
		(void)ft_mtx_actions(&tmp->mtx_full_philos, DESTROY, tmp);
	if (tmp->mtx_stop_sim_init)
		(void)ft_mtx_actions(&tmp->mtx_stop_sim, DESTROY, tmp);
	if (tmp->mtx_print_init)
		(void)ft_mtx_actions(&tmp->mtx_print, DESTROY, tmp);
	free(tmp);
	*sim = NULL;
}
