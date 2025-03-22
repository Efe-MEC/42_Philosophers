/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:20:26 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/22 13:55:43 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_get_status(t_status status)
{
	if (status == EATING)
		return ("is eating");
	else if (status == SLEEPING)
		return ("is sleeping");
	else if (status == THINKING)
		return ("is thinking");
	else if (status == DIED)
		return ("died");
	else if (status == TAKING_FORK)
		return ("has taken a fork");
	else
		return (NULL);
}

bool	ft_print_status(t_philo *philo, t_status status)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&philo->sim->print_mutex);
	printf("%lu %d %s\n", ft_get_time(&philo->sim), philo->id,
		ft_get_status(status));
	if (philo->eaten == philo->arg.req_eat_count)
		ret = true;
	pthread_mutex_unlock(&philo->sim->print_mutex);
	return (ret);
}
