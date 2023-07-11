/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:06:25 by mneri             #+#    #+#             */
/*   Updated: 2023/07/11 16:49:35 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_env	*ft_init_env(char **av)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->stop = malloc(sizeof(int));
	env->num_philo = ft_atoi(av[1]);
	env->die_time = ft_atoi(av[2]);
	env->eat_time = ft_atoi(av[3]);
	env->sleep_time = ft_atoi(av[4]);
	*env->stop = 0;
	if (av[5] != NULL)
		env->num_repeat = ft_atoi(av[5]);
	else
		env->num_repeat = __INT_MAX__;
	if (env->num_philo <= 0 || env->die_time <= 0 || env->eat_time <= 0
		|| env->sleep_time <= 0)
		return (NULL);
	env->init_time = ft_get_time();
	return (env);
}

void	ft_init_mutex(t_env *env)
{
	int		i;

	env->eat_mutex = malloc(sizeof(pthread_mutex_t));
	env->print_mutex = malloc(sizeof(pthread_mutex_t));
	env->fork = malloc(sizeof(pthread_mutex_t) * env->num_philo);
	env->stop_mutex = malloc(sizeof(pthread_mutex_t));
	i = 0;
	pthread_mutex_init(env->stop_mutex, NULL);
	pthread_mutex_init(env->print_mutex, NULL);
	pthread_mutex_init(env->eat_mutex, NULL);
	while (i < env->num_philo)
	{
		pthread_mutex_init(&env->fork[i], NULL);
		i++;
	}
}
