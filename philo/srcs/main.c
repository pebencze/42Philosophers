/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:13:08 by pbencze           #+#    #+#             */
/*   Updated: 2024/06/03 15:09:37 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

int	main(int ac, char **av)
{
	t_info	*info;

	if (ac != 5 && ac != 6)
		return (handle_error_int("usage: 5 to 6 arguments", NULL));
	if (check_args(av))
		return (handle_error_int("invalid arguments", NULL));
	info = info_init(ac, av);
	if (!info)
		return (1);
	if (pthread_create(&(info->monitor), NULL, &ft_monitor, info))
		return (handle_error_int("failed creating monitor", info));
	if (create_philos(info))
		return (handle_error_int(NULL, info));
	if (pthread_join(info->monitor, NULL))
		return (handle_error_int("failure joining", info));
	free_struct(info);
	return (0);
}

int	create_philos(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->number_of_philos)
	{
		if (pthread_create(&(info->philos[i]->thread), NULL,
				&start_routine, info->philos[i]))
			return (handle_error_int("error creating new threads", info));
	}
	i = -1;
	while (++i < info->number_of_philos)
	{
		if (pthread_join(info->philos[i]->thread, NULL) != 0)
			return (handle_error_int("failure on joining threads", info));
	}
	return (0);
}
