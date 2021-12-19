/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 06:20:09 by sotherys          #+#    #+#             */
/*   Updated: 2021/12/19 06:37:34 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_routine_init(t_philo *philo, t_cfg *cfg)
{
	static int	id = 0;

	pthread_mutex_lock(&cfg->mutex[0]);
	philo->id = id++;
	philo->state = PH_THINKING;
	philo->f1 = philo->id % cfg->n;
	philo->f2 = (philo->id + 1) % cfg->n;
	philo->fork_cnt = 0;
	philo->n_eat = 0;
	pthread_mutex_unlock(&cfg->mutex[0]);
	while (!cfg->sim)
		continue ;
	philo->t_last = cfg->t_start;
}

void	ft_routine_take_fork(t_philo *philo, t_cfg *cfg, int fork)
{
	pthread_mutex_lock(&cfg->mutex[fork]);
	if (cfg->forks[fork] == -1)
	{
		cfg->forks[fork] = philo->id;
		++philo->fork_cnt;
	}
	pthread_mutex_unlock(&cfg->mutex[fork]);
}

long	ft_routine_status(t_cfg *cfg, int id, const char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&cfg->generic_mutex);
	timestamp = ft_gettime();
	if (cfg->sim)
		printf("%ld %d %s\n", timestamp - cfg->t_start, id + 1, msg);
	pthread_mutex_unlock(&cfg->generic_mutex);
	return (timestamp);
}

t_bool	ft_routine_check_time(long t_start, long t_d)
{
	long	elapsed;

	elapsed = ft_gettime() - t_start;
	return (elapsed >= t_d);
}
