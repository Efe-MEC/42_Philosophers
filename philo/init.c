/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:30:33 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/25 21:34:06 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_philo(t_philo *philo, t_sim *sim, int id, int nr_philo)
{
	philo->sim = sim;
	philo->id = id + 1;
	philo->meals_eaten = 0;
	philo->left_fork = &sim->forks[id];
	philo->right_fork = &sim->forks[(id + 1) % nr_philo];
	philo->odd = (philo->id % 2 == 1);
	philo->t_last_meal = 0;
	if (!ft_mtx_actions(&philo->mtx_last_meal, INIT, sim))
		return (0);
	philo->mtx_last_meal_init = 1;
	return (1);
}

static int	ft_init_philos(t_sim *sim)
{
	int	i;
	int	nr_philo;

	nr_philo = sim->nr_philo;
	sim->philos = (t_philo *)malloc(sizeof(t_philo) * nr_philo);
	if (!sim->philos)
	{
		ft_exiterr(ERROR_MALLOC, sim);
		return (0);
	}
	i = 0;
	while (i < nr_philo)
	{
		if (!ft_init_philo(&sim->philos[i], sim, i, nr_philo))
		{
			while (i > 0)
				(void)ft_mtx_actions(&sim->philos[--i].mtx_last_meal,
					DESTROY, sim);
			free(sim->philos);
			sim->philos = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

static int	ft_init_forks(t_sim *sim)
{
	int	i;
	int	nr_philo;

	nr_philo = sim->nr_philo;
	sim->forks = (t_fork *)malloc(sizeof(t_fork) * nr_philo);
	if (!sim->forks)
	{
		ft_exiterr(ERROR_MALLOC, sim);
		return (0);
	}
	i = 0;
	while (i < nr_philo)
	{
		if (!ft_mtx_actions(&sim->forks[i].fork, INIT, NULL))
		{
			while (i > 0)
				ft_mtx_actions(&sim->forks[--i].fork, DESTROY, NULL);
			free(sim->forks);
			sim->forks = NULL;
			return (0);
		}
		sim->forks[i].fork_id = i + 1;
		i++;
	}
	return (1);
}

static int	ft_init_state(t_sim *sim, int argc, char **argv)
{
	sim->full_philos = 0;
	sim->stop_sim = 0;
	sim->forks = NULL;
	sim->philos = NULL;
	sim->mtx_print_init = 0;
	sim->mtx_full_philos_init = 0;
	sim->mtx_stop_sim_init = 0;
	if (!ft_init_args(sim, argc, argv))
		return (0);
	sim->t_think = sim->t_die - sim->t_eat - sim->t_sleep;
	if (!ft_mtx_actions(&sim->mtx_print, INIT, NULL))
		return (0);
	sim->mtx_print_init = 1;
	if (!ft_mtx_actions(&sim->mtx_full_philos, INIT, NULL))
		return (0);
	sim->mtx_full_philos_init = 1;
	if (!ft_mtx_actions(&sim->mtx_stop_sim, INIT, NULL))
		return (0);
	sim->mtx_stop_sim_init = 1;
	return (1);
}

int	ft_init_sim(t_sim **sim, int argc, char **argv)
{
	*sim = (t_sim *)malloc(sizeof(t_sim));
	if (!(*sim))
	{
		ft_exiterr(ERROR_MALLOC, *sim);
		return (0);
	}
	if (!ft_init_state(*sim, argc, argv))
		return (0);
	if (!ft_init_forks(*sim))
		return (0);
	if (!ft_init_philos(*sim))
		return (0);
	return (1);
}
