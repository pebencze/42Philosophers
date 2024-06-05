/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:55:54 by pbencze           #+#    #+#             */
/*   Updated: 2024/06/05 11:59:55 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"

typedef struct s_phil {
	pthread_t			thread;
	int					id;
	int					meal_count;
	long				last_meal_time;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_info		*info;
}	t_phil;

typedef struct s_info {
	int					number_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_meals;
	unsigned long		time_to_think;
	long				start_time;
	int					full;
	bool				dead;
	t_phil				**philos;
	pthread_t			monitor;
	pthread_mutex_t		info_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		*fork_mutex;
	bool				info_mutex_flag;
	bool				print_mutex_flag;
	bool				*fork_mutex_flag;
}	t_info;

/*utils*/
long	get_time(void);
int		check_args(char **av);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *nptr);
void	efficient_sleep(long time_in_ms);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strcmp(const char *s1, const char *s2);

/*error*/
int		handle_error_int(char *str, void *ptr);
void	*handle_error_ptr(char *str, void *ptr);

/*init*/
void	free_struct(t_info *info);
int		create_philos(t_info *info);
t_info	*info_init(int ac, char **av);
int		philos_init(t_info *info, int num);
int		vars_init(t_info *info, int ac, char **av);

/*routine*/
void	eat(t_phil *philo);
void	*ft_monitor(void *arg);
void	*start_routine(void *arg);
int		grab_forks(t_phil *philo);
void	*lonely_philo(t_phil *philo);
void	log_event(t_phil *philo, const char *str);
int		check_simulation_end(t_phil *philo);

#endif
