/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:38:28 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/18 19:21:53 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_situation	*stt;

	if (!ft_check_args(argc, argv))
		return (0);
	if (!ft_init(&stt, argc, argv))
		return (0);
}
