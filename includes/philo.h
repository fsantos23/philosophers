/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:52:21 by fsantos2          #+#    #+#             */
/*   Updated: 2024/01/05 13:14:00 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
	int				grab;
	int				owner;
}					t_fork;

typedef struct s_info
{
	int				philos;
	int				fork;
	__uint64_t		die;
	__uint64_t		eat;
	__uint64_t		sleep;
	int				must_eat;
	__uint64_t		begin_tmp;
	t_fork			*forks;
}					t_info;

typedef struct s_dead
{
	int				died;
	int				flag;
}					t_dead;

typedef struct s_philo
{
	int				cur_philo;
	int				have_ate;
	__uint64_t		die;

	pthread_t		thread;
	pthread_mutex_t	mutex;

	t_info			info;
	t_fork			*r_fork;
	t_fork			*l_fork;
	t_dead			dead;
}					t_philo;

int					ft_atoi(const char *str);
void				*ft_calloc(size_t nitems, size_t size);
__uint64_t			get_time(void);
void				*start_philos(void *all);
void				one_philo(t_philo *philo);
int					ft_usleep(__uint64_t time, t_philo *philo);
void				actions(t_philo *philo);
int					check_fork(t_philo *philo);
int					eat(t_philo *philo, __uint64_t time);
int					ft_sleep(t_philo *philo, __uint64_t time);
int					think(t_philo *philo);
int					check_death(t_philo *philo);
void				write_actions(t_philo *philo, char *message);
void				free_philos(t_philo *philo, t_info info);
int					check_args(char **argv);
int					must_eat(t_philo *philo);
int					grab_fork(t_fork *fork);
int					grab_forks(t_philo *philo, t_fork *left, t_fork *right);
int					death_check(t_philo *philo, t_info info, int *i, \
__uint64_t cur_time);

#endif