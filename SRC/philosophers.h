/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:55:11 by mneri             #+#    #+#             */
/*   Updated: 2023/06/23 12:43:19 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct env
{
	int num_philo;
	long int die_time;
	long int	eat_time;
	long int sleep_time;
	int num_repeat;

}	t_env;

typedef struct philo
{
	t_env env;
	pthread_t thread_id;
	int	id;
	pthread_mutex_t fork_mutex;
} t_philo;

long int	ft_atoi(char *str);
int	ft_isdigit(int c);
