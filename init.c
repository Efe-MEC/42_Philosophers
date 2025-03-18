/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:30:33 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/18 19:15:58 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_init_args(t_situation *stt, int argc, char **argv)
{
	stt->arg.philo_count = ft_atoil(argv[1]);
	stt->arg.time_to_die = ft_atoil(argv[2]);
	stt->arg.time_to_eat = ft_atoil(argv[3]);
	stt->arg.time_to_sleep = ft_atoil(argv[4]);
	if (argc == 6)
		stt->arg.must_eat_count = ft_atoil(argv[5]);
	else
		stt->arg.must_eat_count = -1;
}

static int	ft_init_forks(t_situation *stt)
{
	int				i;
	pthread_mutex_t	*mutexes;

	mutexes = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * stt->arg.philo_count);
	if (!mutexes)
		return (0);
	i = 0;
	while (i < stt->arg.philo_count)
	{
		pthread_mutex_init(mutexes + i, NULL);
		i++;
	}
	stt->forks = mutexes;
	return (1);
}

static int	ft_init_philo(t_situation *stt, pthread_t *thds, int32_t i)
{
	stt->philos[i].id = i + 1;
	stt->philos[i].right = &stt->forks[i];
	stt->philos[i].left = NULL;
	stt->philos[i].th = thds[i];
	stt->philos[i].arg = stt->arg;
	stt->philos[i].situation = stt;
	stt->philos[i].is_first_loop = 1;
	stt->philos[i].last_eating_time = 0;
	stt->philos[i].eaten = 0;
}

static int	ft_init_philos(t_situation *stt)
{
	pthread_t	*thds;
	int32_t		i;

	stt->philos = (t_philo *)malloc(sizeof(t_philo) * stt->arg.philo_count);
	if (!stt->philos)
		return (0);
	thds = (pthread_t *)malloc(sizeof(pthread_t) * stt->arg.philo_count);
	if (!thds)
		return (free(stt->philos), 0);
	stt->threads = thds;
	i = 0;
	while (i < stt->arg.philo_count)
	{
		ft_init_philo(stt, thds, i);
		if (stt->arg.philo_count == 1)
			break ;
		if (i == 0)
			stt->philos[i].left = &stt->forks[stt->arg.philo_count - 1];
		else
			stt->philos[i].left = &stt->forks[i - 1];
		i++;
	}
	return (1);
}

int	ft_init(t_situation **stt, int argc, char **argv)
{
	*stt = (t_situation *)malloc(sizeof(t_situation));
	if (!*stt)
		return (ft_exiterr("Error: Malloc failed\n", 1, NULL));
	ft_init_args(*stt, argc, argv);
	if (!ft_init_forks(*stt))
		return (ft_exiterr("Error: Malloc failed\n", 2, *stt));
	if (!ft_init_philos(*stt))
		return (ft_exiterr("Error: Malloc failed\n", 3, *stt));
	pthread_mutex_init(&(*stt)->print_mutex, NULL);
	(*stt)->first_philo_count = (*stt)->arg.philo_count;
	pthread_mutex_init(&(*stt)->first_philos_mutex, NULL);
	pthread_mutex_init(&(*stt)->life_mutex, NULL);
	pthread_mutex_init(&(*stt)->eaten_philo_mutex, NULL);
	(*stt)->life_ended = 0;
	(*stt)->eaten_philo_count = 0;
	(*stt)->is_odd_philos = (*stt)->arg.philo_count % 2;
	return (1);
}

