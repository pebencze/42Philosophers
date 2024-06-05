/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:08:29 by pbencze           #+#    #+#             */
/*   Updated: 2024/06/03 15:08:05 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

t_info	*info_init(int ac, char **av)
{
	int		num;
	t_info	*info;

	num = ft_atoi(av[1]);
	info = ft_calloc(1, sizeof(t_info));
	if (!info)
		return (handle_error_ptr("error on allocation for *info", NULL));
	info->fork_mutex = ft_calloc(num, sizeof(pthread_mutex_t));
	info->fork_mutex_flag = ft_calloc(num, sizeof(bool));
	if (!info->fork_mutex || !info->fork_mutex_flag)
		return (handle_error_ptr("error on allocation for fork_mutex", info));
	if (vars_init(info, ac, av) == 1)
		return (handle_error_ptr(NULL, info));
	if (philos_init(info, num) == 1)
		return (handle_error_ptr(NULL, info));
	if (info->number_of_philos % 2)
		info->time_to_think = (2 * info->time_to_eat) - info->time_to_sleep;
	else
		info->time_to_think = (info->time_to_die - info->time_to_eat
				- info->time_to_sleep) * 0.9;
	if (info->time_to_think > INT_MAX || info->time_to_think < 0)
		info->time_to_think = 0;
	return (info);
}

int	vars_init(t_info *info, int ac, char **av)
{
	int	i;

	info->number_of_philos = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	info->start_time = get_time();
	if (ac == 6)
		info->number_of_meals = ft_atoi(av[5]);
	else
		info->number_of_meals = -1;
	i = -1;
	while (++i < info->number_of_philos)
	{
		if (pthread_mutex_init(&(info->fork_mutex[i]), NULL))
			return (handle_error_int("fork_mutex init has failed", NULL));
		info->fork_mutex_flag[i] = true;
	}
	if (pthread_mutex_init(&(info->info_mutex), NULL))
		return (handle_error_int("info_mutex init has failed", NULL));
	info->info_mutex_flag = true;
	if (pthread_mutex_init(&(info->print_mutex), NULL))
		return (handle_error_int("info_mutex init has failed", NULL));
	info->print_mutex_flag = true;
	return (0);
}

int	philos_init(t_info *info, int num)
{
	int		i;

	info->philos = ft_calloc(num, sizeof(t_phil *));
	if (!info->philos)
		return (handle_error_int("error on allocation for **philos", info));
	i = -1;
	while (++i < num)
	{
		info->philos[i] = ft_calloc(1, sizeof(t_phil));
		if (!info->philos[i])
			return (handle_error_int("error on allocation for *philos", info));
		info->philos[i]->id = i + 1;
		info->philos[i]->info = info;
		info->philos[i]->left_fork = &(info->fork_mutex[i]);
		if (num > 1)
			info->philos[i]->right_fork = &(info->fork_mutex[(i + 1) % num]);
		info->philos[i]->last_meal_time = info->start_time;
	}
	return (0);
}
