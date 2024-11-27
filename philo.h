/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:13:06 by akitsenk          #+#    #+#             */
/*   Updated: 2024/11/21 14:49:28 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	int					num;
	pthread_t			id;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	int					max_meals;
	int					had_meals;
	long long			last_meal;
	long long			start_time;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	pthread_mutex_t		*philomtx;
	int					stop;
	struct s_philo_data	*data;
}						t_philo;

typedef struct s_philo_data
{
	int					philos_count;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	int					max_meals;
	t_philo				*philos;
	pthread_mutex_t		*forks_mutex;
	int					forksm_count;
	pthread_mutex_t		*philo_mutex;
	int					philom_count;
	long long			start_time;
	pthread_mutex_t		stdout_mutex;
	int					stdout_m;
	pthread_t			check_philos;
}						t_philo_data;

void		data_init(int argc, char **argv, t_philo_data	*data);
void		forks_mutex_init(t_philo_data **data);
void		philo_data_mutex_init(t_philo_data **data);
void		philos_init_val(t_philo_data **data, int i);

void		threads_go(t_philo_data *data);

void		time_to_sleep(t_philo *philo);
void		time_to_think(t_philo *philo);
void		*philo_go(void *arg);

void		*philo_check(void *arg);
int			time_to_stop(t_philo *philo);
int			is_dead(t_philo_data *data, t_philo *philo);

//other utils
void		ft_print(char *message, t_philo *philo);
void		set_int(pthread_mutex_t *mutex, int *where, int value);
void		set_long(pthread_mutex_t *mutex, long long *where, long long value);
int			get_int(pthread_mutex_t *mutex, int *from);
long long	get_long(pthread_mutex_t *mutex, long long *from);
void		set_meal(pthread_mutex_t *mutex, int *where);

//time
long long	ft_get_time(void);
void		ft_sleep(int time);

//utils
int			ft_atoi_mod(char *str);

//clean
void		error_message(t_philo_data *data, char *message);
void		clean_before_exit(t_philo_data *data);

//to remove
void		print_data(t_philo_data *data);
void		print_each_philo(t_philo philo);

#endif
