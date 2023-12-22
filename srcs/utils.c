/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsantos2 <fsantos2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:12:13 by fsantos2          #+#    #+#             */
/*   Updated: 2023/12/02 18:01:32 by fsantos2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*ptr;

	ptr = malloc(nitems * size);
	if (ptr)
		memset(ptr, 0, nitems * size);
	return (ptr);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res *= 10;
		res += str[i] - 48;
		i++;
	}
	return (res * sign);
}

int	check_args(char **argv)
{
	int		i;
	int		a;

	a = 1;
	while (argv[a])
	{
		i = 0;
		if (ft_atoi(argv[a]) >= INT_MAX && ft_atoi(argv[a]) <= INT_MIN)
			return (0);
		while (argv[a][i])
		{
			if (argv[a][i] < 48 || argv[a][i] > 57)
				return (0);
			i++;
		}
		a++;
	}
	return (1);
}
