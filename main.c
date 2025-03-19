/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:38:28 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/19 11:40:16 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_sim	*sim;

	sim = NULL;
	if (!ft_check_args(argc, argv))
		return (0);
	if (!ft_init_sim(&sim, argc, argv))
	{
		ft_free_sim(&sim);
		return (0);
	}
	if (!ft_start_sim(sim))
	{
		ft_free_sim(&sim);
		return (0);
	}
	ft_free_sim(&sim);
	return (0);
}
