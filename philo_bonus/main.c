/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 16:51:14 by ybouddou          #+#    #+#             */
/*   Updated: 2021/06/23 08:51:36 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_check(void *args)
{
	t_philo		*philo;
	long		end;

	philo = args;
	while (1)
	{
		usleep(100);
		philo->limit = get_time(philo->start_eat);
		end = get_time(philo->data->start);
		if (philo->limit > philo->data->time_die)
		{
			sem_wait(philo->msg);
			printf("%ld\tPhilosopher %d \033[0;31mdied\033[0m\n",
				end, philo->index + 1);
			sem_post(philo->prog);
			exit(0);
		}
	}
	return (NULL);
}

void	state(t_philo	*philo)
{
	struct timeval	time;

	while (1)
	{
		sem_wait(philo->fork);
		msg(philo, "has taken a fork");
		sem_wait(philo->fork);
		msg(philo, "has taken a fork");
		msg(philo, "\033[0;32mis eating\033[0m");
		gettimeofday(&time, NULL);
		philo->start_eat = (time.tv_sec * 1000) + (time.tv_usec / 1000);
		usleep(philo->data->time_eat * 1000);
		sem_post(philo->fork);
		sem_post(philo->fork);
		msg(philo, "is sleeping");
		usleep(philo->data->time_sleep * 1000);
		msg(philo, "is thinking");
		if (philo->must_eat > 0)
			philo->must_eat--;
		if (!philo->must_eat)
			break ;
	}
	sem_post(philo->eat);
}

void	create_processes(t_philo *philo, int num)
{
	struct timeval	time;
	pthread_t		th_philo;
	int				i;

	sem_wait(philo->prog);
	i = -1;
	while (++i < num)
	{
		philo->pid[i] = fork();
		if (!philo->pid[i])
		{
			philo->index = i;
			gettimeofday(&time, NULL);
			philo->start_eat = (time.tv_sec * 1000) + (time.tv_usec / 1000);
			if (pthread_create(&th_philo, NULL, &death_check, (void *)philo))
				perror("Failed to create thread");
			pthread_detach(th_philo);
			state(philo);
			exit(0);
		}
	}
	sem_wait(philo->prog);
	while (i--)
		kill(philo->pid[i], SIGKILL);
}

void	*eat_check(void *args)
{
	t_philo		*philo;

	philo = args;
	while (1)
	{
		sem_wait(philo->eat);
		philo->counter++;
		if (philo->counter == philo->data->nb_philo)
		{
			sem_post(philo->prog);
			break ;
		}
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philo		philo;
	t_data		data;
	pthread_t	th_eat;

	if (ac < 5 || ac > 6)
		return (err_msg("Error args\n"));
	if (parse_data(&data, av))
		return (1);
	init(&philo, &data);
	if (pthread_create(&th_eat, NULL, &eat_check, (void *)&philo))
		perror("Failed to create thread");
	pthread_detach(th_eat);
	create_processes(&philo, data.nb_philo);
	free(philo.pid);
	return (0);
}
