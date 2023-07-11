/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:57:18 by mneri             #+#    #+#             */
/*   Updated: 2023/07/11 17:22:33 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_check_stop(t_philo *philo)
{
	pthread_mutex_lock(philo->stop_mutex);
	if (*philo->stop != 0)
	{
		pthread_mutex_unlock(philo->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->stop_mutex);
	return (0);
}

void	ft_take_fork_and_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->l_fork < philo->r_fork)
	{
		first_fork = philo->l_fork;
		second_fork = philo->r_fork;
	}
	else
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}
	pthread_mutex_lock(first_fork);
	ft_printlock(philo, "fork");
	pthread_mutex_lock(second_fork);
	ft_printlock(philo, "fork");
	ft_printlock(philo, "eat");
	ft_usleep(philo->env.eat_time);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_lock(philo->eat_mutex);
	philo->last_eat = ft_get_time() - philo->env.init_time;
	philo->times_ate++;
	pthread_mutex_unlock(philo->eat_mutex);
}

int	ft_check_times_ate(t_philo *philo)
{
	int	j;

	j = 0;
	while (j < philo->env.num_philo)
	{
		if (philo[j].times_ate < philo->env.num_repeat)
		{
			return (0);
		}
		j++;
	}
	return (1);
}

int	ft_check_death_stop(t_philo *philo, int i)
{
	unsigned long	time;

	time = ft_get_time() - philo->env.init_time;
	if (time - philo[i].last_eat > philo->env.die_time)
	{
		pthread_mutex_unlock(philo->eat_mutex);
		*philo->stop = 1;
		pthread_mutex_unlock(philo->stop_mutex);
		ft_printlock(&philo[i], "dead");
		return (1);
	}
	if (ft_check_times_ate(philo))
	{
		pthread_mutex_unlock(philo->eat_mutex);
		*philo->stop = 1;
		pthread_mutex_unlock(philo->stop_mutex);
		return (1);
	}
	return (0);
}

void	*ft_examine_philo(void *ptr)
{
	int				i;
	t_philo			*philo;

	philo = ptr;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(philo->stop_mutex);
		pthread_mutex_lock(philo->eat_mutex);
		if (ft_check_death_stop(philo, i))
			return (NULL);
		pthread_mutex_unlock(philo->stop_mutex);
		pthread_mutex_unlock(philo->eat_mutex);
		i++;
		if (i == philo->env.num_philo - 1 || philo->env.num_philo == 1)
			i = 0;
	}
	return (NULL);
}
