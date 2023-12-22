/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:14:13 by fsantos2          #+#    #+#             */
/*   Updated: 2023/12/02 18:53:07 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	must_eat(t_philo *philo)
{
	if (philo->info.must_eat != 0)
	{
		pthread_mutex_lock(&philo->mutex);
		if (philo->have_ate == philo->info.must_eat)
		{
			pthread_mutex_unlock(&philo->mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->mutex);
	}
	return (1);
}

void	write_actions(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->mutex);
	printf("%lu %d %s\n", get_time() - philo->info.begin_tmp, philo->cur_philo, \
		message);
	pthread_mutex_unlock(&philo->mutex);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	if (philo->dead.died == 1)
	{
		pthread_mutex_unlock(&philo->mutex);
		if (philo->dead.flag == 1)
		{
			philo->dead.flag = 0;
			write_actions(philo, "died");
		}
		return (0);
	}
	pthread_mutex_unlock(&philo->mutex);
	return (1);
}

int	grab_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->fork_mutex);
	if (fork->grab != 0)
	{
		pthread_mutex_unlock(&fork->fork_mutex);
		return (0);
	}
	fork->grab = 1;
	return (1);
}

int	grab_forks(t_philo *philo, t_fork *left, t_fork *right)
{
	while (!grab_fork(left))
	{
		if (!ft_usleep(1, philo))
			return (0);
	}
	while (!grab_fork(right))
	{
		if (!ft_usleep(1, philo))
			return (0);
	}
	return (1);
}
