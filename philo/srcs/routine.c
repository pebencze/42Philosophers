/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:12:07 by pbencze           #+#    #+#             */
/*   Updated: 2024/06/05 12:10:48 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	*lonely_philo(t_phil *philo)
{
	pthread_mutex_lock(philo->left_fork);
	log_event(philo, FORK);
	pthread_mutex_unlock(philo->left_fork);
	usleep(philo->info->time_to_die * 1000);
	return (NULL);
}

int	grab_forks(t_phil *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		log_event(philo, FORK);
		pthread_mutex_lock(philo->right_fork);
		log_event(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		log_event(philo, FORK);
		pthread_mutex_lock(philo->left_fork);
		log_event(philo, FORK);
	}
	return (0);
}

void	eat(t_phil *philo)
{
	log_event(philo, EAT);
	pthread_mutex_lock(&(philo->info->info_mutex));
	philo->last_meal_time = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&(philo->info->info_mutex));
	efficient_sleep(philo->info->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*start_routine(void *arg)
{
	t_phil	*philo;

	philo = (t_phil *)arg;
	if (philo->info->number_of_philos == 1)
		return (lonely_philo(philo));
	while (1)
	{
		if (check_simulation_end(philo))
			return (NULL);
		while (grab_forks(philo))
		{
			usleep(50);
		}
		eat(philo);
		log_event(philo, SLEEP);
		efficient_sleep(philo->info->time_to_sleep);
		log_event(philo, THINK);
		efficient_sleep(philo->info->time_to_think);
	}
	return (NULL);
}

void	log_event(t_phil *philo, const char *str)
{
	long	timestamp_in_ms;

	pthread_mutex_lock(&(philo->info->info_mutex));
	if ((philo->info->dead == 1 || philo->info->full
			== philo->info->number_of_philos) && ft_strcmp("died", str))
	{
		pthread_mutex_unlock(&(philo->info->info_mutex));
		return ;
	}
	pthread_mutex_unlock(&(philo->info->info_mutex));
	pthread_mutex_lock(&(philo->info->print_mutex));
	timestamp_in_ms = get_time() - philo->info->start_time;
	printf("\033[95m%lu %i %s\033[0m\n", timestamp_in_ms, philo->id, str);
	pthread_mutex_unlock(&(philo->info->print_mutex));
}
