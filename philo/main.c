/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 16:26:11 by ybouddou          #+#    #+#             */
/*   Updated: 2021/06/23 09:10:52 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_check(void *args)
{
	t_philo		*philo;
	long		end;
	long		limit;

	philo = args;
	while (1)
	{
		if (!philo->must_eat)
			break ;
		usleep(100);
		limit = get_time(philo->start_eat);
		end = get_time(philo->data->start);
		if (limit > philo->data->time_die)
		{
			pthread_mutex_lock(&philo->data->death);
			pthread_mutex_lock(&philo->data->msg);
			printf("%ld\tPhilosopher %d \033[0;31mdied\033[0m\n",
				end, philo->index + 1);
			if (philo->data->nb_philo == 1)
				pthread_mutex_unlock(&philo->data->fork[philo->index]);
			pthread_mutex_unlock(&philo->data->prog);
			break ;
		}
	}
	return (NULL);
}

void	state(t_philo	*philo)
{
	struct timeval	time;
	int				next_fork;

	next_fork = (philo->index + 1) % philo->data->nb_philo;
	pthread_mutex_lock(&philo->data->fork[philo->index]);
	msg(&philo->data->msg, "has taken a fork", philo);
	pthread_mutex_lock(&philo->data->fork[next_fork]);
	msg(&philo->data->msg, "has taken a fork", philo);
	msg(&philo->data->msg, "\033[0;32mis eating\033[0m", philo);
	gettimeofday(&time, NULL);
	philo->start_eat = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	usleep(philo->data->time_eat * 1000);
	pthread_mutex_unlock(&philo->data->fork[philo->index]);
	pthread_mutex_unlock(&philo->data->fork[next_fork]);
	msg(&philo->data->msg, "is sleeping", philo);
	usleep(philo->data->time_sleep * 1000);
	msg(&philo->data->msg, "is thinking", philo);
}

void	*routine(void *args)
{
	struct timeval	time;
	pthread_t		th_philo;
	t_philo			*philo;

	philo = args;
	gettimeofday(&time, NULL);
	philo->start_eat = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (pthread_create(&th_philo, NULL, &death_check, args) != 0)
		perror("Failed to create thread");
	pthread_detach(th_philo);
	while (1)
	{
		state(philo);
		if (philo->must_eat > 0)
			philo->must_eat--;
		if (!philo->must_eat)
			break ;
	}
	philo->data->philos--;
	if (!philo->data->philos)
		pthread_mutex_unlock(&philo->data->prog);
	return (NULL);
}

void	create_threads(t_philo *philo, int num)
{
	pthread_t	th_philo;
	int			i;

	i = -1;
	pthread_mutex_lock(&philo->data->prog);
	while (++i < num)
	{
		if (pthread_create(&th_philo, NULL, &routine, (void *)&philo[i]) != 0)
			perror("Failed to create thread");
		pthread_detach(th_philo);
		usleep(100);
	}
	pthread_mutex_lock(&philo->data->prog);
}

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_data		data;

	if (ac < 5 || ac > 6)
		return (err_msg("Error args\n"));
	if (parse_data(&data, av))
		return (1);
	philo = init(&data);
	create_threads(philo, data.nb_philo);
	free(data.fork);
	free(philo);
	return (0);
}
