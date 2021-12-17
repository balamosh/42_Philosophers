/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 06:20:09 by sotherys          #+#    #+#             */
/*   Updated: 2021/12/17 23:22:27 by sotherys         ###   ########.fr       */
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

t_time	ft_routine_status(t_cfg *cfg, int id, const char *msg)
{
	t_time	t_now;
	long	timestamp;

	gettimeofday(&t_now, NULL);
	timestamp = (t_now.tv_sec - cfg->t_start.tv_sec) * 1000 \
				+ (t_now.tv_usec - cfg->t_start.tv_usec) / 1000;
	printf("%ld %d %s\n", timestamp, id + 1, msg);
	return (t_now);
}

t_bool	ft_routine_check_time(t_time t_start, t_time t_d)
{
	t_time	t_now;
	long	elapsed;

	gettimeofday(&t_now, NULL);
	elapsed = (t_now.tv_sec - t_start.tv_sec) * 1000 \
				+ (t_now.tv_usec - t_start.tv_usec) / 1000;
	return (elapsed >= t_d.tv_sec * 1000 + t_d.tv_usec / 1000);
}
