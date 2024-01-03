/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:54:35 by fsantos2          #+#    #+#             */
/*   Updated: 2024/01/03 23:14:32 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	general_death(t_philo *philo, t_info info, __uint64_t time)
{
	int			i;
	__uint64_t	cur_time;

	i = -1;
	while (i++ < info.philos - 1)
	{
		cur_time = get_time() - time;
		if(!death_check(philo, info, &i, cur_time))
			return (0);
	}
	return (1);
}

void	initialize_threads(t_philo *philo, t_info info)
{
	__uint64_t	time;
	int			i;

	i = -1;
	time = get_time();
	while (i++ < info.philos - 1)
	{
		philo[i].info.begin_tmp = time;
		pthread_create(&philo[i].thread, NULL, start_philos, &philo[i]);
	}
	while (1)
	{
		if (!general_death(philo, info, time))
			break ;
	}
	i = -1;
	while (i++ < info.philos - 1)
	{
		pthread_join(philo[i].thread, NULL);
		pthread_mutex_destroy(&philo[i].mutex);
		pthread_mutex_destroy(&info.forks[i].fork_mutex);
	}
	free(info.forks);
	free(philo);
}

t_info	store_info(char **argv, int argc)
{
	t_info	info;

	if (argc == 6)
		info.must_eat = ft_atoi(argv[5]);
	else
		info.must_eat = 0;
	info.philos = ft_atoi(argv[1]);
	info.die = ft_atoi(argv[2]);
	info.eat = ft_atoi(argv[3]);
	info.sleep = ft_atoi(argv[4]);
	info.fork = info.philos;
	info.begin_tmp = 0;
	return (info);
}

void	create_list(t_info info)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * info.philos);
	info.forks = malloc(sizeof(t_fork) * info.philos);
	if (!philo || !info.forks)
		exit(-1);
	while (i < info.philos)
	{
		pthread_mutex_init(&info.forks[i].fork_mutex, NULL);
		info.forks[i].grab = 0;
		philo[i].cur_philo = i + 1;
		philo[i].info = info;
		philo[i].l_fork = &info.forks[i];
		philo[i].r_fork = &info.forks[(i + 1) % philo->info.philos];
		philo[i].have_ate = 0;
		philo[i].die = info.die;
		philo[i].dead.died = 0;
		philo[i].dead.flag = 0;
		pthread_mutex_init(&philo[i].mutex, NULL);
		i++;
	}
	initialize_threads(philo, info);
}

int	main(int argc, char **argv)
{
	t_info		info;

	if (argc == 5 || argc == 6)
	{
		if (!check_args(argv))
		{
			printf("Please introduct valid arguments\n");
			return (0);
		}
		info = store_info(argv, argc);
		create_list(info);
	}
}
