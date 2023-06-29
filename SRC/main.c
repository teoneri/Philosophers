/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:53:47 by mneri             #+#    #+#             */
/*   Updated: 2023/06/29 17:03:55 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_checkargs_char(char **av)
{
	int i;
	int j;
	i = 1;
	j = 0;
	while (av[i] != NULL)
	{
		while(av[i][j] != '\0')
		{
			if(ft_isdigit(av[i][j]) == 0)
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

t_env *ft_init_env(char **av)
{
	t_env *env;
	
	env = malloc(sizeof(t_env));
	env->num_philo = ft_atoi(av[1]);
	env->die_time = ft_atoi(av[2]);
	env->eat_time = ft_atoi(av[3]);
	env->sleep_time = ft_atoi(av[4]);
	if(av[5] != NULL)
		env->num_repeat = ft_atoi(av[5]);
	if(env->num_philo <=0 || env->die_time <= 0 || env->eat_time <= 0
		|| env->sleep_time <= 0)
			return (NULL);
	env->init_time = ft_get_time();
	return (env);
}

t_philo *ft_init_philo(t_env env, pthread_mutex_t *mutex)
{
	int i;
	t_philo *philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * env.num_philo); 
	while(i < env.num_philo)
	{
		philo[i].env = env;
		philo[i].fork_mutex = mutex;
		pthread_mutex_init(&philo[i].fork_mutex[i], NULL);
		philo[i].times_ate = 0;
		philo[i].id = i + 1;
		i++;
	}
	return (philo);
}


void	*ft_philo(void *ptr)
{
	t_philo *philo;
	int next;
	int id;

	philo = ptr;
	id = philo->id - 1;
	next = ft_getnext_philo(philo);
	if(philo->id % 2 == 0)
		usleep((philo->env.eat_time / 2) * 1000);
	while(1)
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
	return(NULL);
}

void	start_thread(t_philo *philo)
{
	int i;

	i = 0;
	while(i < philo->env.num_philo)
	{
		pthread_create(&philo[i].thread_id, NULL, ft_philo, philo + i);
		i++;
	}
}

void	join_thread(t_philo *philo)
{
	int i;

	i = 0;
	while(i < philo->env.num_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
}


int	main(int ac, char **av)
{
	t_env *env;
	t_philo *philo;
	pthread_mutex_t *mutex;

	if (ac < 5 || ac > 6)
		return 0;
	else
	{
		if (ft_checkargs_char(av) == 0)
			return 0;
		env = ft_init_env(av);
		if (!env)
			return 0;
		mutex = malloc(sizeof(pthread_mutex_t) * env->num_philo);
		philo = ft_init_philo(*env, mutex);
		start_thread(philo);
		ft_examine_philo(philo);
	}
	ft_free(mutex, env, philo);
}