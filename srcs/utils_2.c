/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:38:42 by fsantos2          #+#    #+#             */
/*   Updated: 2023/12/01 14:57:40 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

__uint64_t	get_time(void)
{
	struct timeval	mili;

	gettimeofday(&mili, NULL);
	return (mili.tv_sec * 1000 + mili.tv_usec / 1000);
}

void	*start_philos(void *philo)
{
	t_philo	*philos;

	philos = (t_philo *)philo;
	if (philos->info.philos == 1)
		one_philo(philos);
	else
		actions(philos);
	return (NULL);
}

void	one_philo(t_philo *philo)
{
	printf("0 1 has taken a fork\n");
	ft_usleep(philo->info.die, philo);
	printf("%lu 1 died\n", philo->info.die);
}

int	ft_usleep(__uint64_t time, t_philo *philo)
{
	__uint64_t	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (!check_death(philo))
			return (0);
		usleep(1);
	}
	return (1);
}
