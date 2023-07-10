/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:57:18 by mneri             #+#    #+#             */
/*   Updated: 2023/07/10 19:51:08 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_check_stop(t_philo *philo)
{
	pthread_mutex_lock(philo->stop_mutex);
	if(*philo->stop != 0)
	{
		pthread_mutex_unlock(philo->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->stop_mutex);
	return (0);
	
}

void ft_take_fork_and_eat(t_philo *philo) 
{

    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

    if (philo->l_fork < philo->r_fork) {
        first_fork = philo->l_fork;
        second_fork = philo->r_fork;
    } else {
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
void	*ft_philo(void *ptr)
{
	t_philo *philo;

	philo = ptr;
	
	if (philo->id % 2 == 0)
		ft_usleep(philo->env.eat_time / 2);
	while(!ft_check_stop(philo))
	{
		ft_take_fork_and_eat(philo);
		ft_printlock(philo, "sleep");
		ft_usleep(philo->env.sleep_time);
		ft_printlock(philo, "think");
	}
	return (NULL);
}

int	ft_check_times_ate(t_philo *philo)
{
	int	j;

	j = 0;

	while (j < philo->env.num_philo)
	{
		if (philo[j].times_ate < philo->env.num_repeat)
		{
			return 0;
		}
		j++;
	}
	return (1);
}

void	*ft_examine_philo(void *ptr)
{
	unsigned long	time;
	int				i;
	t_philo *philo;

	philo = ptr;
	i = 0;
	while (1)
	{
		time = ft_get_time() - philo->env.init_time;
		pthread_mutex_lock(philo->stop_mutex);
		pthread_mutex_lock(philo->eat_mutex);
		if (time - philo[i].last_eat >= philo->env.die_time)
		{
			pthread_mutex_unlock(philo->eat_mutex);
			*philo->stop = 1;
			pthread_mutex_unlock(philo->stop_mutex);
			ft_printlock(&philo[i], "dead");
			return (NULL);
		}
		if(ft_check_times_ate(philo))
		{
			pthread_mutex_unlock(philo->eat_mutex);
			*philo->stop = 1;
			pthread_mutex_unlock(philo->stop_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(philo->stop_mutex);
		pthread_mutex_unlock(philo->eat_mutex);
		i++;
		if(i == philo->env.num_philo - 1)
			i = 0;
	}
	return (NULL);
}