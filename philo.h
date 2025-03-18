/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:38:47 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/18 23:48:50 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>

typedef int32_t	t_phid;

typedef struct s_philo
{
	t_phid				id;
	pthread_t			th;
	pthread_mutex_t		*right;
	pthread_mutex_t		*left;
	t_arg				arg;
	struct s_situation	*situation;
	bool				is_first_loop;
	u_int64_t			last_eating_time;
	int32_t				eaten;
}				t_philo;

typedef struct s_arg
{
	int	philo_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_count;
}				t_arg;

typedef struct s_situation
{
	t_arg			arg;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_t		*threads;
	struct timeval	tv;
	uint64_t		start_time;
	bool			is_odd_philos;
	int32_t			first_philo_count;
	pthread_mutex_t	first_philos_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	life_mutex;
	bool			life_ended;
	int32_t			eaten_philo_count;
	pthread_mutex_t	eaten_philo_mutex;
}				t_situation;

int	ft_check_args(int argc, char **argv);
int	ft_init(t_situation **stt, int argc, char **argv);

#endif