/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:31:43 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/22 14:08:03 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(t_sim **sim)
{
	if (!sim || !(*sim))
		return ;
	if ((*sim)->forks)
		free((*sim)->forks);
	if ((*sim)->threads)
		free((*sim)->threads);
	if ((*sim)->philos)
		free((*sim)->philos);
	free(*sim);
	*sim = NULL;
}

int	ft_exiterr(char *msg, int err, t_sim **sim)
{
	ft_exit(sim);
	printf("%s\n", msg);
	return (err);
}
