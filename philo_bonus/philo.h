/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 16:51:31 by ybouddou          #+#    #+#             */
/*   Updated: 2021/06/20 17:01:12 by ybouddou         ###   ########.fr       */
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
# include <semaphore.h>
# include <signal.h>

typedef struct s_data
{
	int		nb_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		must_eat;
	long	start;
	int		dead;
}				t_data;

typedef struct s_philo
{
	int		*pids;
	sem_t	*fork;
	sem_t	*msg;
	sem_t	*prog;
	t_data	*data;
	int		must_eat;
	long	start_eat;
	long	limit;
	int		index;
	int		*pid;
}				t_philo;

// Utils
int		ft_atoi(char *s);
int		is_all_digit(char **str);
int		err_msg(char *msg);
int		ft_strlen(const char *s);
void	init(t_philo *philo, t_data *data);
int		parse_data(t_data *data, char **av);
long	get_time(long start);
void	msg(t_philo *philo, char *msg);

#endif