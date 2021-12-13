/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:33:19 by sotherys          #+#    #+#             */
/*   Updated: 2021/12/13 22:10:15 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_init(t_philo *philo, t_cfg *cfg)
{
	pthread_mutex_lock(&cfg->mutex);
	philo->id = cfg->i;
	philo->state = PH_THINKING;
	philo->ate = cfg->t_start;
	philo->n_eat = 0;
	cfg->thread_cfg = TRUE;
	pthread_mutex_unlock(&cfg->mutex);
}

void	*ft_routine(void *data)
{
	t_cfg	*cfg;
	t_philo	philo;
	t_time	tv;

	cfg = (t_cfg*)data;
	ft_philo_init(&philo, cfg);
	while (cfg->sim)
	{
		if (ft_routine_dead(&philo, cfg))
			break ;
		else if (philo.state == PH_THINKING)
		{
			pthread_mutex_lock(&cfg->mutex);
			if (cfg->forks[philo.id % cfg->n] && cfg->forks[(philo.id + 1) % cfg->n])
			{
				cfg->forks[philo.id % cfg->n] = FALSE;
				gettimeofday(&tv, NULL);
				printf("%ld %d has taken a fork\n", tv.tv_usec, philo.id + 1);
				cfg->forks[(philo.id + 1) % cfg->n] = FALSE;
				gettimeofday(&tv, NULL);
				printf("%ld %d has taken a fork\n", tv.tv_usec, philo.id + 1);
				philo.state = PH_EATING;
				gettimeofday(&tv, NULL);
				printf("%ld %d is eating\n", tv.tv_usec, philo.id + 1);
			}
			pthread_mutex_unlock(&cfg->mutex);
		}
		else if (philo.state == PH_EATING)
		{
			usleep(cfg->t_eat);
			pthread_mutex_lock(&cfg->mutex);
			cfg->forks[philo.id % cfg->n] = TRUE;
			cfg->forks[(philo.id + 1) % cfg->n] = TRUE;
			pthread_mutex_unlock(&cfg->mutex);
			philo.state = PH_SLEEPING;
			gettimeofday(&tv, NULL);
			printf("%ld %d is sleeping\n", tv.tv_usec, philo.id + 1);
			philo.ate = tv.tv_usec;
			++philo.n_eat;
		}
		else if (philo.state == PH_SLEEPING)
		{
			usleep(cfg->t_sleep);
			gettimeofday(&tv, NULL);
			philo.state = PH_THINKING;
			printf("%ld %d is thinking\n", tv.tv_usec, philo.id + 1);
		}
	}
	pthread_detach(cfg->tid[philo.id]);
	return (NULL);
}
