/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 21:39:49 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/22 13:35:32 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_minus_first_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->first_philos_mutex);
	if (philo->sim->first_philo_count > 0)
		philo->sim->first_philo_count--;
	pthread_mutex_unlock(&philo->sim->first_philos_mutex);
}

bool	ft_is_finish_first(t_philo *philo)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&philo->sim->first_philos_mutex);
	if (philo->sim->first_philo_count == 0)
		ret = true;
	pthread_mutex_unlock(&philo->sim->first_philos_mutex);
	return (ret);
}
