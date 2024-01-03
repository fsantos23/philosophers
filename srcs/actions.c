/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:28:45 by fsantos2          #+#    #+#             */
/*   Updated: 2024/01/03 18:52:51 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	actions(t_philo *philo)
{
	__uint64_t	time;

	pthread_mutex_lock(&philo->mutex);
	time = philo->die;
	if (philo->cur_philo % 2 == 0)
		usleep(50);
	pthread_mutex_unlock(&philo->mutex);
	while (1)
	{
		if (!check_death(philo))
			break ;
		if (check_fork(philo) == 0)
		{
			if (eat(philo, time) == 1)
				break ;
			if (!must_eat(philo))
				break ;
			if (ft_sleep(philo, time) == 1)	
				break ;
			if (think(philo) == 1)
				break ;
		}
		if (!check_death(philo))
			break ;
	}
}

int	check_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	if (philo->cur_philo % 2 == 0)
	{
		pthread_mutex_unlock(&philo->mutex);
		if (!grab_forks(philo, philo->l_fork, philo->r_fork))
			return (1);
		write_actions(philo, "has taken a fork");
		write_actions(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_unlock(&philo->mutex);
		if (!grab_forks(philo, philo->r_fork, philo->l_fork))
			return (1);
		write_actions(philo, "has taken a fork");
		write_actions(philo, "has taken a fork");
	}
	if (!check_death(philo))
	{
		pthread_mutex_unlock(&philo->r_fork->fork_mutex);
		pthread_mutex_unlock(&philo->l_fork->fork_mutex);
		return (1);
	}
	return (0);
}

int	eat(t_philo *philo, __uint64_t time)
{
	pthread_mutex_unlock(&philo->r_fork->fork_mutex);
	pthread_mutex_unlock(&philo->l_fork->fork_mutex);
	if (!check_death(philo))
		return (1);
	write_actions(philo, "is eating");
	if (!ft_usleep(philo->info.eat, philo))
		return (1);
	if (!check_death(philo))
		return (1);
	pthread_mutex_lock(&philo->r_fork->fork_mutex);
	philo->r_fork->grab = 0;
	pthread_mutex_unlock(&philo->r_fork->fork_mutex);
	pthread_mutex_lock(&philo->l_fork->fork_mutex);
	philo->l_fork->grab = 0;
	pthread_mutex_unlock(&philo->l_fork->fork_mutex);
	pthread_mutex_lock(&philo->mutex);
	philo->have_ate++;
	philo->die += time;
	pthread_mutex_unlock(&philo->mutex);
	return (0);
}

int	ft_sleep(t_philo *philo, __uint64_t time)
{
	if (!check_death(philo))
		return (1);
	pthread_mutex_lock(&philo->mutex);
	philo->die += time;
	pthread_mutex_unlock(&philo->mutex);
	write_actions(philo, "is sleeping");
	if (!ft_usleep(philo->info.sleep, philo))
		return (1);
	if (!check_death(philo))
		return (1);
	return (0);
}

int	think(t_philo *philo)
{
	if (!check_death(philo))
		return (1);
	write_actions(philo, "is thinking");
	if (!ft_usleep(100, philo))
		return (1);
	return (0);
}
