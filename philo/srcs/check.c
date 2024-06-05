/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:47:55 by pbencze           #+#    #+#             */
/*   Updated: 2024/06/03 12:19:47 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static int	check_digit(char *str)
{
	while (*str)
	{
		if (*str > 57 || *str < 48)
			return (1);
		str++;
	}
	return (0);
}

static long	ft_atol(const char *nptr)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		nbr = nbr * 10 + (nptr[i] - 48);
		i++;
	}
	return (nbr);
}

int	check_args(char **av)
{
	long	num;
	int		i;

	i = 1;
	while (av[i])
	{
		if (check_digit(av[i]))
			return (1);
		if (ft_strlen(av[1]) > 10)
			return (1);
		num = ft_atol(av[i]);
		if (num > INT_MAX || num == 0)
			return (1);
		i++;
	}
	return (0);
}
