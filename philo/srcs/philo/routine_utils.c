/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 06:20:09 by sotherys          #+#    #+#             */
/*   Updated: 2022/06/22 21:01:31 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_routine_init(t_cfg *cfg)
{
	static int	id = 0;
	t_philo		*philo;

	pthread_mutex_lock(&cfg->mutex);
	philo = &cfg->philo[id++];
	pthread_mutex_unlock(&cfg->mutex);
	philo->f1 = philo->id % cfg->n;
	philo->f2 = (philo->id + 1) % cfg->n;
	if (philo->f2 > philo->f1)
		ft_swap(&philo->f1, &philo->f2);
	philo->state = PH_TAKES_FORK;
	philo->n_eat = 0;
	return (philo);
}

long	ft_routine_status(t_cfg *cfg, t_philo *philo)
{
	static const char	*msg[5] = \
	{"has taken a fork", "is eating", "is sleeping", "is thinking", "died"};
	long				timestamp;

	pthread_mutex_lock(&cfg->print);
	timestamp = ft_gettime();
	pthread_mutex_lock(&philo->mutex);
	if (philo->sim)
		printf("%ld %d %s\n", \
				timestamp - cfg->t_start, philo->id + 1, msg[philo->state]);
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&cfg->print);
	return (timestamp);
}

t_bool	ft_routine_check_time(long t_start, long t_d)
{
	long	elapsed;

	elapsed = ft_gettime() - t_start;
	return (elapsed >= t_d);
}

void	ft_routine_wait(t_philo *philo, long t_last, long t_d)
{
	t_bool	sim;

	sim = TRUE;
	while (!ft_routine_check_time(t_last, t_d) && sim)
	{
		pthread_mutex_lock(&philo->mutex);
		sim = philo->sim;
		pthread_mutex_unlock(&philo->mutex);
	}
}
