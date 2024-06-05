/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:56:51 by pbencze           #+#    #+#             */
/*   Updated: 2024/06/05 11:59:08 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	check_simulation_end(t_phil *philo)
{
	pthread_mutex_lock(&(philo->info->info_mutex));
	if (philo->meal_count == philo->info->number_of_meals)
		philo->info->full++;
	if (philo->info->dead == 1 || philo->info->full
		== philo->info->number_of_philos)
	{
		pthread_mutex_unlock(&(philo->info->info_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->info->info_mutex));
	return (0);
}

static int	check_meals(t_info *info)
{
	pthread_mutex_lock(&(info->info_mutex));
	if (info->full == info->number_of_philos)
	{
		pthread_mutex_unlock(&(info->info_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(info->info_mutex));
	return (0);
}

void	*ft_monitor(void *arg)
{
	t_info	*info;
	int		i;

	info = (t_info *)arg;
	while (1)
	{
		if (check_meals(info))
			return (NULL);
		i = -1;
		while (++i < info->number_of_philos)
		{
			pthread_mutex_lock(&(info->info_mutex));
			if ((get_time() - info->philos[i]->last_meal_time)
				>= info->time_to_die)
			{
				info->dead = 1;
				pthread_mutex_unlock(&(info->info_mutex));
				log_event(info->philos[i], "died");
				return (NULL);
			}
			pthread_mutex_unlock(&(info->info_mutex));
		}
		usleep(100);
	}
	return (NULL);
}
