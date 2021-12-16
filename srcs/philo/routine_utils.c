/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 06:20:09 by sotherys          #+#    #+#             */
/*   Updated: 2021/12/16 03:01:46 by sotherys         ###   ########.fr       */
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
	while(!cfg->sim)
		continue ;
	philo->t_last = cfg->t_start;
}

void	ft_routine_take_fork(t_philo *philo, t_cfg *cfg, int fork)
{
	pthread_mutex_lock(&cfg->mutex[fork]);
	//printf("%d got the mutex[%d]\n", philo->id + 1, fork);
	if (cfg->forks[fork])
	{
		cfg->forks[fork] = FALSE;
		++philo->fork_cnt;
		//ft_routine_status(cfg->t_start, philo->id, "has taken a fork");
	}
	pthread_mutex_unlock(&cfg->mutex[fork]);
	//printf("%d released the mutex[%d]\n", philo->id + 1, fork);
}

t_time	ft_routine_status(t_time t_start, int id, const char *msg)
{
	t_time	t_now;
	long	timestamp;

	gettimeofday(&t_now, NULL);
	timestamp = (t_now.tv_sec - t_start.tv_sec) * 1000000 \
				+ t_now.tv_usec - t_start.tv_usec;
	printf("%ld %d %s\n", timestamp, id + 1, msg);
	return (t_now);
}

t_bool	ft_routine_check_time(t_time t_start, t_time t_d)
{
	t_time	t_now;
	long	elapsed;

	gettimeofday(&t_now, NULL);
	elapsed = (t_now.tv_sec - t_start.tv_sec) * 1000000 \
				+ t_now.tv_usec - t_start.tv_usec;
	return (elapsed >= t_d.tv_sec * 1000000 + t_d.tv_usec);
}
