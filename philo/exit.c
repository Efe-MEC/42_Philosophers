/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:31:43 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/23 17:57:37 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(t_sim **sim)
{
	int	i;

	if (!sim || !(*sim))
		return ;

	if ((*sim)->philos)
		free((*sim)->philos);
	if ((*sim)->forks)
	{
		i = 0;
		while (i < (*sim)->arg.philo_count)
			pthread_mutex_destroy(&(*sim)->forks[i++]);
		free((*sim)->forks);
	}
	if ((*sim)->threads)
		free((*sim)->threads);
	free(*sim);
	*sim = NULL;
}

int	ft_exiterr(char *msg, int err, t_sim **sim)
{
	ft_exit(sim);
	printf("%s\n", msg);
	return (err);
}
