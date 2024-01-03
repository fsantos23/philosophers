/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 23:08:24 by fsantos2          #+#    #+#             */
/*   Updated: 2024/01/03 23:13:18 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void bs(t_philo *philo, t_info info, int *i)
{
	while ((*i) < info.philos)
	{
		pthread_mutex_lock(&philo[*i].mutex);
		philo[*i].dead.died = 1;
		pthread_mutex_unlock(&philo[*i].mutex);
		(*i)++;
	}
}

int more_bs(t_philo *philo, t_info info, int *i, int *a)
{
    
    while((*i) < info.philos)
	{
		pthread_mutex_lock(&philo[*i].mutex);
		if(philo[*i].have_ate == info.must_eat)
		{
			(*a)++;
			if(*a == info.philos)
			{
				pthread_mutex_unlock(&philo[*i].mutex);
				return (0);
			}
		}
		pthread_mutex_unlock(&philo[*i].mutex);
		(*i)++;
	}
    return (1);
}

int death_check(t_philo *philo, t_info info, int *i, __uint64_t cur_time)
{
	int a;
	
	a = 0;
	pthread_mutex_lock(&philo[*i].mutex);
	if (cur_time >= philo[*i].die)
	{
		philo[*i].dead.flag = 1;
		pthread_mutex_unlock(&philo[*i].mutex);
		(*i) = 0;
		bs(philo, info, i);
		return (0);
	}
	else if (philo[*i].info.must_eat != 0)
	{
		pthread_mutex_unlock(&philo[*i].mutex);
        (*i) = 0;
		if(!more_bs(philo, info, i, &a))
            return (0);
	}
	else
		pthread_mutex_unlock(&philo[*i].mutex);
	return 1;
}