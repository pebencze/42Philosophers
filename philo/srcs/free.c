/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:10:10 by pbencze           #+#    #+#             */
/*   Updated: 2024/06/03 15:06:51 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static void	free_mutexes(t_info *info)
{
	if (info->info_mutex_flag)
	{
		if (pthread_mutex_destroy(&(info->info_mutex)))
			handle_error_int("failure on destroying info mutex", NULL);
	}
	if (info->print_mutex_flag)
	{
		if (pthread_mutex_destroy(&(info->print_mutex)))
			handle_error_int("failure on destroying print mutex", NULL);
	}
}

static void	free_philos(t_info *info)
{
	int	i;

	if (info->philos)
	{
		i = -1;
		while (++i < info->number_of_philos)
			free(info->philos[i]);
		free(info->philos);
	}
}

static void	free_forks(t_info *info)
{
	int	i;

	if (info->fork_mutex_flag)
	{
		i = -1;
		while (++i < info->number_of_philos)
		{
			if (info->fork_mutex_flag[i] && info->fork_mutex
				&& pthread_mutex_destroy(&(info->fork_mutex[i])))
				handle_error_int("failure on destroying fork mutex", NULL);
		}
		free(info->fork_mutex_flag);
		free(info->fork_mutex);
	}
}

void	free_struct(t_info *info)
{
	if (info)
	{
		free_forks(info);
		free_mutexes(info);
		free_philos(info);
		free(info);
	}
}
