/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:33:19 by sotherys          #+#    #+#             */
/*   Updated: 2022/06/19 04:50:27 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_routine_take_fork(t_philo *philo, t_cfg *cfg)
{
	if (philo->f1 == philo->f2)
		return ;
	pthread_mutex_lock(&cfg->fork[philo->f1]);
	ft_routine_status(cfg, philo);
	pthread_mutex_lock(&cfg->fork[philo->f2]);
	ft_routine_status(cfg, philo);
	philo->state = PH_EATING;
}

void	ft_routine_eating(t_philo *philo, t_cfg *cfg)
{
	pthread_mutex_lock(&cfg->time[philo->id]);
	philo->t_last = ft_routine_status(cfg, philo);
	pthread_mutex_unlock(&cfg->time[philo->id]);
	ft_routine_wait(philo, cfg->t_eat);
	philo->state = PH_SLEEPING;
	pthread_mutex_unlock(&cfg->fork[philo->f2]);
	pthread_mutex_unlock(&cfg->fork[philo->f1]);
	++philo->n_eat;
}

void	ft_routine_sleeping(t_philo *philo, t_cfg *cfg)
{
	ft_routine_status(cfg, philo);
	ft_routine_wait(philo, cfg->t_eat + cfg->t_sleep);
	philo->state = PH_THINKING;
}

void	ft_routine_thinking(t_philo *philo, t_cfg *cfg)
{
	ft_routine_status(cfg, philo);
	philo->state = PH_TAKES_FORK;
}

void	*ft_routine(void *data)
{
	t_cfg	*cfg;
	t_philo	*philo;
	t_bool	sim;

	cfg = (t_cfg *)data;
	philo = ft_routine_init(cfg);
	if (philo->id % 2 == 0)
		ft_routine_wait(philo, cfg->t_sleep);
	sim = TRUE;
	while (sim)
	{
		if (philo->state == PH_TAKES_FORK)
			ft_routine_take_fork(philo, cfg);
		if (philo->state == PH_EATING)
			ft_routine_eating(philo, cfg);
		if (philo->state == PH_SLEEPING)
			ft_routine_sleeping(philo, cfg);
		if (philo->state == PH_THINKING)
			ft_routine_thinking(philo, cfg);
		pthread_mutex_lock(&philo->mutex_sim);
		if (!philo->sim)
			sim = FALSE;
		pthread_mutex_unlock(&philo->mutex_sim);
	}
	return (NULL);
}
