/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:26:58 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/22 18:46:44 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_print_status(t_ull time, t_philo *philo, t_action action)
{
	if (action == FORK_L)
		(void)printf("%llu %d %s\n", time, philo->id, "has taken a fork");
	else if (action == FORK_R)
		(void)printf("%llu %d %s\n", time, philo->id, "has taken a fork");
	else if (action == EAT)
		(void)printf("%llu %d %s\n", time, philo->id, "is eating");
	else if (action == SLEEP)
		(void)printf("%llu %d %s\n", time, philo->id, "is sleeping");
	else if (action == THINK)
		(void)printf("%llu %d %s\n", time, philo->id, "is thinking");
	else if (action == DIE)
		(void)printf("%llu %d %s\n", time, philo->id, "died");
	else if (action == STUFFED)
		(void)printf("%llu %d %s\n", time, philo->id, "is full");
	return (1);
}

int	ft_print_actions(t_ull time, t_philo *philo, t_action action, int upt_time)
{
	if (!ft_mtx_actions(&philo->sim->mtx_stop_sim, LOCK, philo->sim))
		return (0);
	if (philo->sim->stop_sim && action != DIE)
	{
		if (!ft_mtx_actions(&philo->sim->mtx_stop_sim, UNLOCK, philo->sim))
			return (0);
		return (1);
	}
	if (!ft_mtx_actions(&philo->sim->mtx_stop_sim, UNLOCK, philo->sim))
		return (0);
	if (!ft_mtx_actions(&philo->sim->mtx_print, LOCK, philo->sim))
		return (0);
	if (upt_time)
		time = ft_get_time() - philo->sim->t_start_sim;
	ft_print_status(time, philo, action);
	if (!ft_mtx_actions(&philo->sim->mtx_print, UNLOCK, philo->sim))
		return (0);
	return (1);
}

void	ft_exiterr(char *msg, t_sim *sim)
{
	if (sim && sim->mtx_print_init)
		(void)ft_mtx_actions(&sim->mtx_print, LOCK, NULL);
	printf("%s", msg);
	if (sim && sim->mtx_print_init)
		(void)ft_mtx_actions(&sim->mtx_print, UNLOCK, NULL);
}
