/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:45:24 by mneri             #+#    #+#             */
/*   Updated: 2023/06/30 17:03:16 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_one_philo(t_philo *philo)
{
	ft_philo_act(philo, "fork");
	while (philo->stop == 0)
		usleep(1);
}

int	ft_check_to_stop(t_philo *philo, int i, int time, int flag)
{
	if (time - philo[i].last_eat >= philo->env.die_time)
	{
		ft_philo_stop(philo);
		printf("\e[31mPhilosopher %d has died\n", philo[i].id);
		return (1);
	}
	if (ft_check_times_ate(philo) == 1 && flag == 1)
	{
		ft_philo_stop(philo);
		printf("\e[31mAll philosophers have finished eating");
		return (1);
	}
	return (0);
}

void	ft_actions(t_philo *philo, int id, int next)
{
	pthread_mutex_lock(&philo->fork_mutex[id]);
	ft_philo_act(philo, "fork");
	pthread_mutex_lock(&philo->fork_mutex[next]);
	ft_philo_act(philo, "fork");
	ft_philo_act(philo, "eat");
	usleep(philo->env.eat_time * 1000);
	pthread_mutex_unlock(&philo->fork_mutex[id]);
	pthread_mutex_unlock(&philo->fork_mutex[next]);
	ft_philo_act(philo, "sleep");
	usleep(philo->env.sleep_time * 1000);
	ft_philo_act(philo, "think");
}

void	*ft_philo(void *ptr)
{
	t_philo	*philo;
	int		next;
	int		id;

	philo = ptr;
	id = philo->id - 1;
	next = ft_getnext_philo(philo);
	if (philo->id % 2 == 0)
		usleep((philo->env.eat_time / 2) * 1000);
	if (philo->env.num_philo == 1)
		ft_one_philo(philo);
	else
	{
		while (philo->stop == 0)
		{
			ft_actions(philo, id, next);
		}
	}
	return (NULL);
}

void	start_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->env.num_philo)
	{
		pthread_create(&philo[i].thread_id, NULL, ft_philo, philo + i);
		i++;
	}
}
