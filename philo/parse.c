/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:23:00 by ybouddou          #+#    #+#             */
/*   Updated: 2021/06/23 09:09:41 by ybouddou         ###   ########.fr       */
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

void	msg(pthread_mutex_t	*mutex, char *msg, t_philo *philo)
{
	struct timeval	time;
	long			end;

	gettimeofday(&time, NULL);
	end = get_time(philo->data->start);
	pthread_mutex_lock(mutex);
	printf("%ld\tPhilosopher %d %s\n", end, philo->index + 1, msg);
	pthread_mutex_unlock(mutex);
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
	data->philos = data->nb_philo;
	return (0);
}

t_philo	*init(t_data *data)
{
	t_philo			*philo;
	int				i;

	i = data->nb_philo;
	philo = (t_philo *)malloc(sizeof(t_philo) * data->nb_philo);
	data->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * i);
	pthread_mutex_init(&data->msg, NULL);
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->prog, NULL);
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_init(&data->fork[i], NULL);
	i = -1;
	while (++i < data->nb_philo)
	{
		philo[i].data = data;
		philo[i].must_eat = data->must_eat;
		philo[i].index = i;
	}
	return (philo);
}
