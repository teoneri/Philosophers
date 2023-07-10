/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:23:02 by mneri             #+#    #+#             */
/*   Updated: 2023/07/10 19:32:30 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(unsigned long int time_in_ms)
{
	unsigned long int	start_time;

	start_time = 0;
	start_time = ft_get_time();
	while ((ft_get_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

unsigned long	ft_get_time(void)
{
	unsigned long	time;
	struct timeval	t;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (time);
}

void	ft_printlock(t_philo *philo, char *set)
{
	pthread_mutex_lock(philo->print_mutex);
	if(!ft_strncmp(set, "fork", 4) && !ft_check_stop(philo))
	{
		printf("%ld %d has taken a fork\n", (ft_get_time() - philo->env.init_time), philo->id);
	}	
	else if(!ft_strncmp(set, "eat", 3) && !ft_check_stop(philo))
	{
		printf("%ld %d is eating\n", (ft_get_time() - philo->env.init_time), philo->id);
	}
	else if(!ft_strncmp(set, "think", 5) && !ft_check_stop(philo))
	{
		printf("%ld %d is thinking\n", (ft_get_time() - philo->env.init_time), philo->id);
	}
	else if(!ft_strncmp(set, "sleep", 5) && !ft_check_stop(philo))
	{
		printf("%ld %d is sleeping\n", (ft_get_time() - philo->env.init_time), philo->id);
	}
	else if(!ft_strncmp(set, "dead", 5) )
	{
		printf("\e[31m%ld %d is dead\n", (ft_get_time() - philo->env.init_time), philo->id);
	}	
	else if(!ft_strncmp(set, "eaten", 5) )
	{
		printf("\e[31m%ld %d is dead\n", (ft_get_time() - philo->env.init_time), philo->id);
	}
	pthread_mutex_unlock(philo->print_mutex);
}

void	ft_free(t_env *env, t_philo *philo)
{
	int i;

	i = 0;
	while(i < env->num_philo)
	{
		pthread_mutex_destroy(&env->fork[i]);	
		i++;
	}
	free(env->fork);
	pthread_mutex_destroy(env->eat_mutex);
	free(env->eat_mutex);
	pthread_mutex_destroy(env->print_mutex);
	free(env->print_mutex);
	pthread_mutex_destroy(env->stop_mutex);
	free(env->stop_mutex);
	free(env->stop);
	free(philo);
}