/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:11:07 by pbencze           #+#    #+#             */
/*   Updated: 2024/06/03 15:16:16 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

int	handle_error_int(char *str, void *ptr)
{
	if (str)
	{
		write(2, "\033[0;31m", 8);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		write(2, "\033[0m", 5);
	}
	if (ptr)
		free_struct((t_info *)ptr);
	return (1);
}

void	*handle_error_ptr(char *str, void *ptr)
{
	if (str)
	{
		write(2, "\033[0;31m", 8);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		write(2, "\033[0m", 5);
	}
	if (ptr)
		free_struct((t_info *)ptr);
	return (NULL);
}
