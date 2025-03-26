/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:19:19 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/22 18:35:20 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_mtx_apply_action(t_mtx *mutex, t_mtx_action action)
{
	if (action == INIT)
	{
		if (pthread_mutex_init(mutex, NULL))
			return (INIT);
	}
	else if (action == LOCK)
	{
		if (pthread_mutex_lock(mutex))
			return (LOCK);
	}
	else if (action == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex))
			return (UNLOCK);
	}
	else if (action == DESTROY)
	{
		if (pthread_mutex_destroy(mutex))
			return (DESTROY);
	}
	return (0);
}

int	ft_mtx_actions(t_mtx *mutex, t_mtx_action action, t_sim *sim)
{
	int	err;

	err = ft_mtx_apply_action(mutex, action);
	if (err)
	{
		if (err == INIT)
			ft_exiterr("Error: Mutex could not generated\n", sim);
		else if (err == LOCK)
			ft_exiterr("Error: Mutex could not locked\n", sim);
		else if (err == UNLOCK)
			ft_exiterr("Error: Mutex could not unlocked\n", sim);
		else if (err == DESTROY)
			ft_exiterr("Error: Mutex could not destroyed\n", sim);
		return (0);
	}
	return (1);
}
