/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:17:53 by pbencze           #+#    #+#             */
/*   Updated: 2024/06/03 15:16:04 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nbr;

	nbr = 0;
	i = 0;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		nbr = nbr * 10 + (nptr[i] - 48);
		i++;
	}
	return (nbr);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	memset(ptr, 0, nmemb * size);
	return (ptr);
}

long	get_time(void)
{
	struct timeval	current_time;
	long			timestamp_in_ms;

	gettimeofday(&current_time, NULL);
	timestamp_in_ms = (current_time.tv_sec * 1000)
		+ (current_time.tv_usec / 1000);
	return (timestamp_in_ms);
}

void	efficient_sleep(long time_in_ms)
{
	long	start;

	if (!time_in_ms)
		return ;
	start = get_time();
	usleep(time_in_ms * 1000 * 90 / 100);
	while (get_time() - start < time_in_ms)
		usleep(500);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i])
		i++;
	return (s1[i] - s2[i]);
}
