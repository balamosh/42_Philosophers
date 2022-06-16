/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 06:20:09 by sotherys          #+#    #+#             */
/*   Updated: 2022/06/16 04:46:14 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_routine_init(t_philo *philo, t_cfg *cfg)
{
	static int	id = 0;

	pthread_mutex_lock(&cfg->generic_mutex);
	philo->id = id++;
	philo->t_start = cfg->t_start;
	philo->t_eat = cfg->t_eat;
	philo->t_sleep = cfg->t_sleep;
	philo->t_die = cfg->t_die;
	philo->n_eat = cfg->n_eat;
	philo->f1 = philo->id % cfg->n;
	philo->f2 = (philo->id + 1) % cfg->n;
	pthread_mutex_unlock(&cfg->generic_mutex);
	philo->t_last = philo->t_start;
	philo->state = PH_THINKING;
	philo->fork_cnt = 0;
	philo->curr_eat = 0;
}

void	ft_routine_take_fork(t_philo *philo, t_cfg *cfg, int fork)
{
	//pthread_mutex_lock(&cfg->generic_mutex);
	pthread_mutex_lock(&cfg->mutex[fork]);
	if (cfg->forks[fork] == -1)
	{
		cfg->forks[fork] = philo->id;
		++philo->fork_cnt;
	}
	pthread_mutex_unlock(&cfg->mutex[fork]);
	//pthread_mutex_unlock(&cfg->generic_mutex);
}

long	ft_routine_status(t_cfg *cfg, t_philo *philo)
{
	static const char	*msg[5] = \
	{"has taken a fork", "is eating", "is sleeping", "is thinking", "died"};
	long				timestamp;

	//timestamp = philo->timestamp;
	pthread_mutex_lock(&cfg->mutex_sim);
	//pthread_mutex_lock(&cfg->generic_mutex);
	timestamp = ft_gettime();
	if (cfg->sim)
		printf("%ld %d %s\n", timestamp - philo->t_start, philo->id + 1, msg[philo->state]);
	if (philo->state == PH_DEAD)
		cfg->sim = FALSE;
	//pthread_mutex_unlock(&cfg->generic_mutex);
	pthread_mutex_unlock(&cfg->mutex_sim);
	return (timestamp);
}

t_bool	ft_routine_check_time(long t_start, long t_d)
{
	long	elapsed;

	elapsed = ft_gettime() - t_start;
	return (elapsed >= t_d);
}
