/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:35:52 by mneri             #+#    #+#             */
/*   Updated: 2023/07/11 16:15:55 by mneri            ###   ########.fr       */
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
	int					*stop;
	pthread_t			exam;
	pthread_mutex_t		*stop_mutex;
	pthread_mutex_t		*fork;
	pthread_mutex_t		*eat_mutex;
	pthread_mutex_t		*print_mutex;
}	t_env;

typedef struct philo
{
	t_env			env;
	pthread_t		thread_id;
	int				id;
	unsigned long	last_eat;
	int				times_ate;
	int				enough;
	int				*stop;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*stop_mutex;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*eat_mutex;
	pthread_mutex_t	*print_mutex;

}	t_philo;

long int		ft_atoi(char *str);
int				ft_isdigit(int c);
void			ft_printlock(t_philo *philo, char *set);
unsigned long	ft_get_time(void);
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
t_env			*ft_init_env(char **av);
void			*ft_examine_philo(void *ptr);
void			start_thread(t_philo *philo, t_env *env);
void			*ft_philo(void *ptr);
void			ft_one_philo(t_philo *philo);
int				ft_check_death(t_philo *philo, int i);
void			ft_usleep(unsigned long int time_in_ms);
int				ft_check_times_ate(t_philo *philo);
void			ft_philo_eat(t_philo *philo);
void			ft_init_mutex(t_env *env);
int				ft_check_stop(t_philo *philo);
void			ft_free(t_env *env, t_philo *philo);
void			ft_take_fork_and_eat(t_philo *philo);

#endif