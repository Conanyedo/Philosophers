/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 16:34:11 by ybouddou          #+#    #+#             */
/*   Updated: 2021/06/20 19:14:36 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	long			start;
	pthread_mutex_t	*fork;
	pthread_mutex_t	prog;
	pthread_mutex_t	msg;
	pthread_mutex_t	death;
}				t_data;

typedef struct s_philo
{
	t_data			*data;
	int				must_eat;
	long			start_eat;
	int				index;
}				t_philo;

// Utils
int		ft_atoi(char *s);
int		is_all_digit(char **str);
int		err_msg(char *msg);
int		ft_strlen(const char *s);
t_philo	*init(t_data *data);
int		parse_data(t_data *data, char **av);
long	get_time(long start);
void	msg(pthread_mutex_t	*mutex, char *msg, t_philo *philo);

#endif