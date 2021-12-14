/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 06:20:09 by sotherys          #+#    #+#             */
/*   Updated: 2021/12/14 06:22:32 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_routine_init(t_philo *philo, t_cfg *cfg)
{
	pthread_mutex_lock(&cfg->mutex);
	philo->id = cfg->i;
	philo->state = PH_THINKING;
	philo->t_last = cfg->t_start;
	philo->n_eat = 0;
	cfg->thread_cfg = TRUE;
	pthread_mutex_unlock(&cfg->mutex);
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
