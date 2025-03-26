/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 20:16:58 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/26 21:02:47 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_max_meal_full(t_philo *philo, int max_meal)
{
	if (philo->meals_eaten != max_meal)
		return (0);
	if (!ft_mtx_actions(&philo->sim->mtx_full_philos, LOCK, philo->sim))
		return (0);
	philo->sim->full_philos++;
	if (!ft_mtx_actions(&philo->sim->mtx_full_philos, UNLOCK, philo->sim))
		return (0);
	if (!ft_print_actions(0, philo, STUFFED, 1))
		return (0);
	if (!ft_print_actions(0, philo, THINK, 1))
		return (0);
	return (1);
}

int	ft_sleep(t_philo *philo, int sleep_time)
{
	if (!ft_print_actions(0, philo, SLEEP, 1))
		return (0);
	if (!ft_wait(sleep_time))
		return (0);
	return (1);
}

int	ft_think(t_philo *philo, int think_time)
{
	if (!ft_print_actions(0, philo, THINK, 1))
		return (0);
	if (!ft_wait(think_time * 0.9))
		return (0);
	return (1);
}

int	ft_check_meal(t_philo *philo, int max_meal)
{
	if (max_meal == 0)
	{
		if (!ft_print_actions(0, philo, STUFFED, 1))
			return (0);
		if (!ft_print_actions(0, philo, THINK, 1))
			return (0);
		return (0);
	}
	return (1);
}
