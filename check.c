/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehcakir <mehcakir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:52:51 by mehcakir          #+#    #+#             */
/*   Updated: 2025/03/18 18:21:57 by mehcakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_digit(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_check_philo_count(char *philo_number)
{
	if (philo_number[0] == '0')
	{
		printf("Error: Philosopher count can not be 0\n");
		return (0);
	}
	return (1);
}

static int	ft_check_arg_count(int argc)
{
	if (!(argc == 5 || argc == 6))
	{
		printf("Error: Wrong number of arguments\n");
		return (0);
	}
	return (1);
}

int	ft_check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i <= (argc - 1))
	{
		if (!ft_is_digit(argv[i]))
		{
			printf("Error: Argument is not a number\n");
			return (0);
		}
		i++;
	}
	if (!ft_check_arg_count(argc) || !ft_check_philo_count(argv[1]))
		return (0);
	return (1);
}
