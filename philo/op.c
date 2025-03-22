/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 21:13:59 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/22 13:56:45 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_think_one_odd(t_philo *philo)
{
	pthread_detach(philo->th);
	if (philo->sim->is_odd_philos && philo->id == 1)
	{
		ft_think(philo);
		philo->is_first_loop = 0;
	}
}

bool	ft_think(t_philo *philo)
{
	if (philo->is_first_loop)
		ft_minus_first_philo(philo);
	return (ft_print_status(philo, THINKING));
}

bool	ft_sleep_think(t_philo *philo)
{
	if (ft_print_status(philo, SLEEPING))
		return (true);
	ft_usleep(&philo->sim, philo->arg.time_to_sleep);
	return (ft_think(philo));
}

static void	ft_life_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->life_mutex);
	philo->last_eating_time = ft_get_time(&philo->sim);
	philo->eaten++;
	pthread_mutex_lock(&philo->sim->eaten_philo_mutex);
	if (philo->eaten == philo->arg.req_eat_count)
		philo->sim->eaten_philo_count++;
	pthread_mutex_unlock(&philo->sim->eaten_philo_mutex);
	pthread_mutex_unlock(&philo->sim->life_mutex);
}

bool	ft_eat(t_philo *philo)
{
	if (philo->right == NULL || philo->left == NULL)
		return (true);
	if (philo->eaten == philo->arg.req_eat_count)
		return (true);
	pthread_mutex_lock(philo->right);
	if (ft_print_status(philo, TAKING_FORK))
		return (pthread_mutex_unlock(philo->right), true);
	pthread_mutex_lock(philo->left);
	if (ft_print_status(philo, TAKING_FORK))
		return (pthread_mutex_unlock(philo->right),
			pthread_mutex_unlock(philo->left), true);
	if (philo->is_first_loop)
		ft_minus_first_philo(philo);
	if (ft_print_status(philo, EATING))
		return (pthread_mutex_unlock(philo->right),
			pthread_mutex_unlock(philo->left), true);
	ft_life_eating(philo);
	ft_usleep(&philo->sim, philo->arg.time_to_eat);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (ft_sleep_think(philo));
}
