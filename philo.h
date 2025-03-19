/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:38:47 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/19 11:58:36 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <sys/time.h>

# define ERROR_MALLOC "Error: malloc failed\n"

typedef pthread_mutex_t		t_mtx;
typedef unsigned long long	t_ull;

typedef enum e_mtx_action
{
	INIT = 1,
	LOCK,
	UNLOCK,
	DESTROY
}	t_mtx_action;

typedef enum e_action
{
	FORK_L,
	FORK_R,
	EAT,
	SLEEP,
	THINK,
	DIE,
	STUFFED
}	t_action;

typedef struct s_fork
{
	int		fork_id;
	t_mtx	fork;
}	t_fork;

typedef struct s_philo
{
	t_sim		*sim;
	int			id;
	int			odd;
	pthread_t	thread_id;
	int			meals_eaten;
	t_ull		t_last_meal;
	t_mtx		mtx_last_meal;
	int			mtx_last_meal_init;
	t_ull		timestamp_death;
	t_fork		*left_fork;
	t_fork		*right_fork;
}	t_philo;

typedef struct s_sim
{
	int			nr_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			t_think;
	int			max_meals;
	int			full_philos;
	int			stop_sim;
	t_ull		t_start_sim;
	t_fork		*forks;
	t_philo		*philos;
	pthread_t	monitor;
	t_mtx		mtx_print;
	int			mtx_print_init;
	t_mtx		mtx_full_philos;
	int			mtx_full_philos_init;
	t_mtx		mtx_stop_sim;
	int			mtx_stop_sim_init;
}	t_sim;

int	ft_init_args(t_sim *sim, int argc, char **argv);

#endif
