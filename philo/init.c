/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:30:33 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/20 01:11:50 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_init_args(t_sim *sim, int argc, char **argv)
{
	sim->arg.philo_count = ft_atoi(argv[1]);
	sim->arg.time_to_die = ft_atoi(argv[2]);
	sim->arg.time_to_eat = ft_atoi(argv[3]);
	sim->arg.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		sim->arg.req_eat_count = ft_atoi(argv[5]);
	else
		sim->arg.req_eat_count = -1;
}

static int	ft_init_forks(t_sim *sim)
{
	int				i;
	pthread_mutex_t	*mutexes;

	mutexes = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * sim->arg.philo_count);
	if (!mutexes)
		return (0);
	i = 0;
	while (i < sim->arg.philo_count)
	{
		pthread_mutex_init(mutexes + i, NULL);
		i++;
	}
	sim->forks = mutexes;
	return (1);
}

static int	ft_init_philo(t_sim *sim, pthread_t *thds, int32_t i)
{
	sim->philos[i].id = i + 1;
	sim->philos[i].right = &sim->forks[i];
	sim->philos[i].left = NULL;
	sim->philos[i].th = thds[i];
	sim->philos[i].arg = sim->arg;
	sim->philos[i].sim = sim;
	sim->philos[i].is_first_loop = 1;
	sim->philos[i].last_eating_time = 0;
	sim->philos[i].eaten = 0;
}

static int	ft_init_philos(t_sim *sim)
{
	pthread_t	*thds;
	int32_t		i;

	sim->philos = (t_philo *)malloc(sizeof(t_philo) * sim->arg.philo_count);
	if (!sim->philos)
		return (0);
	thds = (pthread_t *)malloc(sizeof(pthread_t) * sim->arg.philo_count);
	if (!thds)
		return (free(sim->philos), 0);
	sim->threads = thds;
	i = 0;
	while (i < sim->arg.philo_count)
	{
		ft_init_philo(sim, thds, i);
		if (sim->arg.philo_count == 1)
			break ;
		if (i == 0)
			sim->philos[i].left = &sim->forks[sim->arg.philo_count - 1];
		else
			sim->philos[i].left = &sim->forks[i - 1];
		i++;
	}
	return (1);
}

int	ft_init(t_sim **sim, int argc, char **argv)
{
	*sim = (t_sim *)malloc(sizeof(t_sim));
	if (!*sim)
		return (ft_exiterr("Error: Malloc failed\n", 1, NULL));
	ft_init_args(*sim, argc, argv);
	if (!ft_init_forks(*sim))
		return (ft_exiterr("Error: Malloc failed\n", 2, *sim));
	if (!ft_init_philos(*sim))
		return (ft_exiterr("Error: Malloc failed\n", 3, *sim));
	pthread_mutex_init(&(*sim)->print_mutex, NULL);
	(*sim)->first_philo_count = (*sim)->arg.philo_count;
	pthread_mutex_init(&(*sim)->first_philos_mutex, NULL);
	pthread_mutex_init(&(*sim)->life_mutex, NULL);
	pthread_mutex_init(&(*sim)->eaten_philo_mutex, NULL);
	(*sim)->life_ended = 0;
	(*sim)->eaten_philo_count = 0;
	(*sim)->is_odd_philos = (*sim)->arg.philo_count % 2;
	return (1);
}

