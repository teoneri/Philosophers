/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:21:27 by mneri             #+#    #+#             */
/*   Updated: 2023/06/29 16:29:04 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_philo_act(t_philo *philo, char *act)
{
	unsigned long time;

	time = ft_get_time() - philo->env.init_time;

	if(!ft_strncmp(act, "eat", 3))
	{
		printf("%ld %d is eating\n", time, philo->id);
		philo->last_eat = ft_get_time() - philo->env.init_time;
		philo->times_ate++;
	}
	else if(!ft_strncmp(act, "fork", 4))
		printf("%ld %d has taken a fork\n", time, philo->id);
	else if(!ft_strncmp(act, "think", 5))
		printf("%ld %d is thinking\n", time, philo->id);
	else if(!ft_strncmp(act, "sleep", 5))
		printf("%ld %d is sleeping\n", time, philo->id);
}


int ft_check_times_ate(t_philo *philo)
{
	int j;

	j = 0;

	while (j <= philo->env.num_philo )
	{
		if (philo[j].times_ate < philo->env.num_repeat)
			break;
		j++;
	}
	if (j > philo->env.num_philo - 1)
		return 1;
	return 0;
}

void	ft_examine_philo(t_philo *philo)
{
	int flag;
	unsigned long time;
	int	i;

	i = 0;
	flag = 1;
	if(philo->env.num_repeat == 0)
		flag = 0;
	while(1)
	{
		usleep(1000);
		time = ft_get_time() - philo->env.init_time;
		if(time - philo[i].last_eat >= philo->env.die_time)
		{
			printf("\e[31mPhilosopher %d has died\n", philo[i].id);
			return ;
		}
		if(ft_check_times_ate(philo) == 1 && flag == 1)
		{
			printf("\e[31mAll philosophers have finished eating after having ate %d times\n", philo[i].times_ate);
			return ;
		}
		i++;
		if(i == philo->env.num_philo - 1)
			i = 0;
	}
}

unsigned long ft_get_time(void)
{
	unsigned long time;
	struct timeval t;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (time);
}