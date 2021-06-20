/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 16:51:26 by ybouddou          #+#    #+#             */
/*   Updated: 2021/06/20 20:09:18 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(long start)
{
	struct timeval	time;
	long			end;

	gettimeofday(&time, NULL);
	end = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (end - start);
}

void	msg(t_philo *philo, char *msg)
{
	struct timeval	time;
	long			end;

	gettimeofday(&time, NULL);
	end = get_time(philo->data->start);
	sem_wait(philo->msg);
	printf("%ld\tPhilosopher %d %s\n", end, philo->index + 1, msg);
	sem_post(philo->msg);
}

int	parse_data(t_data *data, char **av)
{
	struct timeval	time;

	*data = (t_data){0};
	if (!is_all_digit(av))
		return (err_msg("Error args\n"));
	data->nb_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	data->must_eat = -1;
	if (av[5])
		data->must_eat = ft_atoi(av[5]);
	if (data->nb_philo < 1 || data->nb_philo > 200 || data->time_die < 60
		|| data->time_eat < 60 || data->time_sleep < 60)
		return (err_msg("Error args\n"));
	gettimeofday(&time, NULL);
	data->start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (0);
}

void	init(t_philo *philo, t_data *data)
{
	sem_unlink("fork");
	sem_unlink("msg");
	sem_unlink("prog");
	philo->fork = sem_open("fork", O_CREAT, 0666, data->nb_philo);
	philo->msg = sem_open("msg", O_CREAT, 0666, 1);
	philo->prog = sem_open("prog", O_CREAT, 0666, 1);
	philo->data = data;
	philo->must_eat = data->must_eat;
	philo->pid = (int *)malloc(sizeof(int) * data->nb_philo);
}
