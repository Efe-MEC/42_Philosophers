/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:15:25 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/26 20:57:18 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_stop_sim(t_philo *philo)
{
	int	dead;

	if (!ft_mtx_actions(&philo->sim->mtx_stop_sim, LOCK, philo->sim))
		return (0);
	dead = philo->sim->stop_sim;
	if (!ft_mtx_actions(&philo->sim->mtx_stop_sim, UNLOCK, philo->sim))
		return (0);
	return (dead);
}

static int	ft_drop_forks(t_philo *philo)
{
	if (philo->odd)
	{
		if (!ft_mtx_actions(&philo->right_fork->fork, UNLOCK, philo->sim))
			return (0);
		if (!ft_mtx_actions(&philo->left_fork->fork, UNLOCK, philo->sim))
			return (0);
	}
	else
	{
		if (!ft_mtx_actions(&philo->left_fork->fork, UNLOCK, philo->sim))
			return (0);
		if (!ft_mtx_actions(&philo->right_fork->fork, UNLOCK, philo->sim))
			return (0);
	}
	return (1);
}

static int	ft_eat(t_philo *philo, int eat_time)
{
	philo->meals_eaten++;
	if (!ft_mtx_actions(&philo->mtx_last_meal, LOCK, philo->sim))
	{
		ft_drop_forks(philo);
		return (0);
	}
	philo->t_last_meal = ft_get_time();
	if (philo->t_last_meal == 0)
	{
		(void)ft_mtx_actions(&philo->mtx_last_meal, UNLOCK, philo->sim);
		ft_drop_forks(philo);
		return (0);
	}
	if (!ft_mtx_actions(&philo->mtx_last_meal, UNLOCK, philo->sim)
		|| !ft_print_actions(0, philo, EAT, 1) || !ft_wait(eat_time))
	{
		ft_drop_forks(philo);
		return (0);
	}
	if (!ft_drop_forks(philo))
		return (0);
	return (1);
}

static int	ft_take_forks(t_philo *philo)
{
	if (philo->odd)
	{
		if (!ft_mtx_actions(&philo->left_fork->fork, LOCK, philo->sim))
			return (0);
		if (!ft_print_actions(0, philo, FORK_L, 1))
			return (0);
		if (!ft_mtx_actions(&philo->right_fork->fork, LOCK, philo->sim))
			return (0);
		if (!ft_print_actions(0, philo, FORK_R, 1))
			return (0);
	}
	else
	{
		(void)usleep(900);
		if (!ft_mtx_actions(&philo->right_fork->fork, LOCK, philo->sim))
			return (0);
		if (!ft_print_actions(0, philo, FORK_R, 1))
			return (0);
		if (!ft_mtx_actions(&philo->left_fork->fork, LOCK, philo->sim))
			return (0);
		if (!ft_print_actions(0, philo, FORK_L, 1))
			return (0);
	}
	return (1);
}

void	*ft_ops(void *arg)
{
	t_philo	*philo;
	int		eat_time;
	int		sleep_time;
	int		think_time;
	int		max_meal;

	philo = (t_philo *)arg;
	eat_time = philo->sim->t_eat;
	sleep_time = philo->sim->t_sleep;
	think_time = philo->sim->t_think;
	max_meal = philo->sim->max_meals;
	if (!ft_check_meal(philo, max_meal))
		return (NULL);
	while (ft_stop_sim(philo) == 0)
	{
		(void)ft_take_forks(philo);
		(void)ft_eat(philo, eat_time);
		if (ft_check_max_meal_full(philo, max_meal))
			return (NULL);
		(void)ft_sleep(philo, sleep_time);
		(void)ft_think(philo, think_time);
	}
	return (NULL);
}
