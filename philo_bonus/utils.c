/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 16:51:36 by ybouddou          #+#    #+#             */
/*   Updated: 2021/06/23 09:26:14 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	err_msg(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (1);
}

int	ft_atoi(char *s)
{
	int		a;

	a = 0;
	while (*s >= '0' && *s <= '9')
	{
		a = (a * 10) + (*s - '0');
		s++;
	}
	return (a);
}

int	is_all_digit(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] < '0' || str[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
