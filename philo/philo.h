/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:38:47 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/22 14:29:32 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdint.h>

typedef int32_t	t_phid;

typedef struct s_arg
{
	int	philo_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	req_eat_count;
}				t_arg;

typedef struct s_philo
{
	t_phid				id;
	pthread_t			th;
	pthread_mutex_t		*right;
	pthread_mutex_t		*left;
	t_arg				arg;
	struct s_sim		*sim;
	bool				is_first_loop;
	uint64_t			last_eating_time;
	int32_t				eaten;
}				t_philo;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	TAKING_FORK,
	NONE
}	t_status;

typedef struct s_sim
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
}				t_sim;

int			ft_check_args(int argc, char **argv);
int			ft_init(t_sim **sim, int argc, char **argv);
int			ft_exiterr(char *msg, int err, t_sim **sim);
int			ft_atoi(const char *str);
uint64_t	ft_get_time(t_sim **sim);
char		*ft_get_status(t_status status);
void		ft_minus_first_philo(t_philo *philo);
void		ft_think_one_odd(t_philo *philo);
void		ft_usleep(t_sim **sim, uint64_t time);
void		ft_exit(t_sim **sim);
bool		ft_is_finish_first(t_philo *philo);
bool		ft_think(t_philo *philo);
bool		ft_sleep_think(t_philo *philo);
bool		ft_eat(t_philo *philo);
bool		ft_print_status(t_philo *philo, t_status status);

#endif