/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:55:11 by mneri             #+#    #+#             */
/*   Updated: 2023/06/30 17:08:12 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct env
{
	int					num_philo;
	unsigned long int	die_time;
	unsigned long int	eat_time;
	unsigned long int	sleep_time;
	int					num_repeat;
	unsigned long		init_time;
}	t_env;

typedef struct philo
{
	t_env			env;
	pthread_t		thread_id;
	int				id;
	pthread_mutex_t	*fork_mutex;
	unsigned long	last_eat;
	int				times_ate;
	int				stop;
}	t_philo;

long int		ft_atoi(char *str);
int				ft_isdigit(int c);
int				ft_getnext_philo(t_philo *philo);
unsigned long	ft_get_time(void);
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
void			ft_philo_act(t_philo *philo, char *act);
void			ft_examine_philo(t_philo *philo);
void			ft_free(pthread_mutex_t *mutex, t_env *env, t_philo *philo);
void			start_thread(t_philo *philo);
void			*ft_philo(void *ptr);
void			ft_one_philo(t_philo *philo);
int				ft_check_to_stop(t_philo *philo, int i, int time, int flag);
void			ft_philo_stop(t_philo *philo);
int				ft_check_times_ate(t_philo *philo);

#endif