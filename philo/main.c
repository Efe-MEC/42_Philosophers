/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:38:28 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/19 21:16:10 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_monitor(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->eaten_philo_mutex);
	if (philo->sim->eaten_philo_count >= philo->sim->arg.philo_count)
		return (0);
	pthread_mutex_unlock(&philo->sim->eaten_philo_mutex);
	pthread_mutex_lock(&philo->sim->print_mutex);
	pthread_mutex_lock(&philo->sim->life_mutex);
	if (ft_get_time(&philo->sim) - philo->last_eating_time
		>= (uint64_t) philo->arg.time_to_die)
	{
		printf("%lu %d %s\n", ft_get_time(&philo->sim), philo->id,
			ft_get_status(DIED));
		return (0);
	}
	pthread_mutex_unlock(&philo->sim->print_mutex);
	pthread_mutex_unlock(&philo->sim->life_mutex);
	return (1);
}

static void	*ft_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_think_one_odd(philo);
	while (1)
	{
		if (philo->is_first_loop)
		{
			if (philo->id % 2 == 1)
			{
				if (ft_eat(philo))
					return (NULL);
			}
			else
			{
				if (ft_think(philo))
					return (NULL);
			}
			philo->is_first_loop = 0;
		}
		if (ft_is_finish_first_loop(philo))
			if (ft_eat(philo))
				return (NULL);
	}
	return (NULL);
}

static void	ft_start(t_sim **sim)
{
	int	i;

	i = 0;
	(*sim)->start_time = ft_get_time();
	while (i < (*sim)->arg.philo_count)
	{
		pthread_create(&(*sim)->philos[i].th, NULL,
			ft_loop, &(*sim)->philos[i]);
		i++;
	}
	while (1)
	{
		i = 0;
		while (i < (*sim)->arg.philo_count)
		{
			if (ft_monitor(&(*sim)->philos[i]) != 1)
			{
				ft_free(*sim);
				return ;
			}
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_sim	*sim;

	if (!ft_check_args(argc, argv))
		return (0);
	if (!ft_init(&sim, argc, argv))
		return (0);
	ft_start(&sim);
}
