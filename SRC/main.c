/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:35:03 by mneri             #+#    #+#             */
/*   Updated: 2023/07/11 16:23:52 by mneri            ###   ########.fr       */
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

t_philo	*ft_init_philo(t_env *env)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * env->num_philo); 
	while (i < env->num_philo)
	{
		philo[i].id = i + 1;
		if (i != env->num_philo - 1)
			philo[i].r_fork = &env->fork[philo[i].id];
		else
			philo[i].r_fork = &env->fork[0];
		philo[i].l_fork = &env->fork[philo[i].id - 1];
		philo[i].eat_mutex = env->eat_mutex;
		philo[i].print_mutex = env->print_mutex;
		philo[i].stop_mutex = env->stop_mutex;
		philo[i].env = *env;
		philo[i].times_ate = 0;
		philo[i].last_eat = 0;
		philo[i].stop = env->stop;
		philo[i].enough = 0;
		i++;
	}
	return (philo);
}

void	*ft_philo(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (philo->id % 2 == 0)
		ft_usleep(philo->env.eat_time / 2);
	if (philo->env.num_philo == 1)
	{
		ft_one_philo(philo);
		return (NULL);
	}
	while (!ft_check_stop(philo))
	{
		ft_take_fork_and_eat(philo);
		ft_printlock(philo, "sleep");
		ft_usleep(philo->env.sleep_time);
		ft_printlock(philo, "think");
	}
	return (NULL);
}

void	start_thread(t_philo *philo, t_env *env)
{
	int	i;

	i = 0;
	while (i < philo->env.num_philo)
	{
		pthread_create(&philo[i].thread_id, NULL, ft_philo, &philo[i]);
		i++;
	}
	pthread_create(&env->exam, NULL, ft_examine_philo, philo);
	while (i--)
	{
		pthread_join(philo[i].thread_id, NULL);
	}
	pthread_join(env->exam, NULL);
}

int	main(int ac, char **av)
{
	t_env			*env;
	t_philo			*philo;

	if (ac < 5 || ac > 6)
		return (0);
	else
	{
		if (ft_checkargs_char(av) == 0)
			return (0);
		env = ft_init_env(av);
		if (!env)
			return (0);
		ft_init_mutex(env);
		philo = ft_init_philo(env);
		start_thread(philo, env);
	}
	ft_free(env, philo);
	free(env);
}
