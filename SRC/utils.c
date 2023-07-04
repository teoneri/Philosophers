/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:07:39 by mneri             #+#    #+#             */
/*   Updated: 2023/07/04 19:30:32 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	ft_atoi(char *str)
{
	long long int	res;
	long long int	sign;
	long long int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (c);
	else
		return (0);
}

int	ft_getnext_philo(t_philo *philo)
{
	int	next;

	if (philo->env.num_philo == 1)
		next = philo->id - 1;
	if (philo->id == 1)
		next = philo->env.num_philo - 1;
	else
		next = philo->id - 2;
	return (next);
}

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int		i;
	unsigned char		*t1;
	unsigned char		*t2;

	if (s1 == NULL || s2 == NULL)
		return (0);
	t1 = (unsigned char *) s1;
	t2 = (unsigned char *) s2;
	i = 0;
	while ((t1[i] != '\0' || t2[i] != '\0') && i < n)
	{
		if (t1[i] == t2[i])
			i++;
		else
			return (t1[i] - t2[i]);
	}
	return (0);
}

void	ft_free(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->env.num_philo)
	{
		pthread_mutex_destroy(philo[i].l_fork);
		pthread_mutex_destroy(philo[i].r_fork);
		pthread_mutex_destroy(&philo[i].print_mutex);
		i++;
	}
}
