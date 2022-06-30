/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:33:19 by sotherys          #+#    #+#             */
/*   Updated: 2022/06/30 14:54:09 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_routine_take_fork(t_philo *philo, t_cfg *cfg)
{
	if (cfg->n < 2)
		return ;
	sem_wait(cfg->take_fork);
	sem_wait(cfg->fork);
	ft_routine_status(cfg, philo);
	sem_wait(cfg->fork);
	ft_routine_status(cfg, philo);
	sem_post(cfg->take_fork);
	philo->state = PH_EATING;
}

void	ft_routine_eating(t_philo *philo, t_cfg *cfg)
{
	pthread_mutex_lock(&philo->time_mutex);
	philo->t_last = ft_routine_status(cfg, philo);
	pthread_mutex_unlock(&philo->time_mutex);
	ft_routine_wait(philo->t_last, cfg->t_eat);
	if (++philo->n_eat == cfg->n_eat)
	{
		sem_wait(cfg->print);
		sem_post(cfg->full);
	}
	philo->state = PH_SLEEPING;
	sem_post(cfg->fork);
	sem_post(cfg->fork);
}

void	ft_routine_sleeping(t_philo *philo, t_cfg *cfg)
{
	long	t_sleep_start;

	t_sleep_start = ft_routine_status(cfg, philo);
	ft_routine_wait(t_sleep_start, cfg->t_sleep);
	philo->state = PH_THINKING;
}

void	ft_routine_thinking(t_philo *philo, t_cfg *cfg)
{
	ft_routine_status(cfg, philo);
	philo->state = PH_TAKES_FORK;
}

void	ft_routine(t_cfg *cfg, t_philo *philo)
{
	t_bool	sim;

	if (!ft_routine_init(cfg, philo))
		return ;
	sim = TRUE;
	while (sim)
	{
		ft_routine_take_fork(philo, cfg);
		ft_routine_eating(philo, cfg);
		ft_routine_sleeping(philo, cfg);
		ft_routine_thinking(philo, cfg);
		pthread_mutex_lock(&philo->sim_mutex);
		sim = philo->sim;
		pthread_mutex_unlock(&philo->sim_mutex);
	}
	printf("%d FINISHED\n", philo->id);
}
