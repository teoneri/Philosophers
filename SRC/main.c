/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:53:47 by mneri             #+#    #+#             */
/*   Updated: 2023/06/30 16:51:10 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_checkargs_char(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i] != NULL)
	{
		while (av[i][j] != '\0')
		{
			if (ft_isdigit(av[i][j]) == 0)
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

t_env	*ft_init_env(char **av)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->num_philo = ft_atoi(av[1]);
	env->die_time = ft_atoi(av[2]);
	env->eat_time = ft_atoi(av[3]);
	env->sleep_time = ft_atoi(av[4]);
	if (av[5] != NULL)
		env->num_repeat = ft_atoi(av[5]);
	else
		env->num_repeat = 0;
	if (env->num_philo <= 0 || env->die_time <= 0 || env->eat_time <= 0
		|| env->sleep_time <= 0)
		return (NULL);
	env->init_time = ft_get_time();
	return (env);
}

t_philo	*ft_init_philo(t_env env, pthread_mutex_t *mutex)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * env.num_philo); 
	while (i < env.num_philo)
	{
		philo[i].env = env;
		philo[i].fork_mutex = mutex;
		pthread_mutex_init(&philo[i].fork_mutex[i], NULL);
		philo[i].times_ate = 0;
		philo[i].id = i + 1;
		philo[i].last_eat = 0;
		philo[i].stop = 0;
		i++;
	}
	return (philo);
}

int	main(int ac, char **av)
{
	t_env			*env;
	t_philo			*philo;
	pthread_mutex_t	*mutex;

	if (ac < 5 || ac > 6)
		return (0);
	else
	{
		if (ft_checkargs_char(av) == 0)
			return (0);
		env = ft_init_env(av);
		if (!env)
			return (0);
		mutex = malloc(sizeof(pthread_mutex_t) * env->num_philo);
		philo = ft_init_philo(*env, mutex);
		start_thread(philo);
		ft_examine_philo(philo);
	}
	ft_free(mutex, env, philo);
}
