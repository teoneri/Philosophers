/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:59:24 by mneri             #+#    #+#             */
/*   Updated: 2023/07/11 16:05:54 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	ft_atoi(char *str)
{
	long long int	res;
	long long int	sign;
	long long int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (c);
	else
		return (0);
}

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int		i;
	unsigned char		*t1;
	unsigned char		*t2;

	if (s1 == NULL || s2 == NULL)
		return (0);
	t1 = (unsigned char *) s1;
	t2 = (unsigned char *) s2;
	i = 0;
	while ((t1[i] != '\0' || t2[i] != '\0') && i < n)
	{
		if (t1[i] == t2[i])
			i++;
		else
			return (t1[i] - t2[i]);
	}
	return (0);
}
