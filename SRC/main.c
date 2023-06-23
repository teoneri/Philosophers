/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:53:47 by mneri             #+#    #+#             */
/*   Updated: 2023/06/23 12:59:32 by mneri            ###   ########.fr       */
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
	return (env);
}

t_philo *ft_init_philo(t_env env)
{
	int i;
	t_philo *philo;

	i = 0;
	philo = malloc(sizeof(t_philo *) * env.num_philo); 
	while(i < env.num_philo)
	{
		philo[i].env = env;
		philo->id = i + 1;
		i++;
	}
	return (philo);
}

void	philo_eat(t_philo *philo)
{
	printf("philosopher %d is eating", philo->id);
}

void	ft_philo(void *ptr)
{
	t_philo *philo;
	int next;

	philo = ptr;
	if(philo->id == philo->env.num_philo)
		next = 0;
	else 
		next = philo->id + 1;
	pthread_mutex_lock(&philo->fork_mutex);
	pthread_mutex_lock(&philo[next].fork_mutex);
	philo_eat(philo);
	
}

void	start_thread(t_philo *philo)
{
	int i;

	i = 0;
	while(i < philo->env.num_philo)
	{
		pthread_create(&philo[i].id, NULL, ft_philo, philo + i);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_env *env;
	t_philo *philo;

	if (ac < 5 || ac > 6)
		return 0;
	else
	{
		if(ft_checkargs_char(av) == 0)
			return 0;
		env = ft_init_env(av);
		if	(!env)
			return 0;
		philo = ft_init_philo(*env);
		while
	}
}