/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:33:19 by sotherys          #+#    #+#             */
/*   Updated: 2022/06/20 14:58:37 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_routine_take_fork(t_philo *philo, t_cfg *cfg)
{
	if (cfg->n < 2)
		return ;
	sem_wait(cfg->fork);
	ft_routine_status(cfg, philo);
	sem_wait(cfg->fork);
	ft_routine_status(cfg, philo);
	philo->state = PH_EATING;
}

void	ft_routine_eating(t_philo *philo, t_cfg *cfg)
{
	pthread_mutex_lock(&philo->time_mutex);
	philo->t_last = ft_routine_status(cfg, philo);
	pthread_mutex_unlock(&philo->time_mutex);
	ft_routine_wait(philo, cfg->t_eat);
	philo->state = PH_SLEEPING;
	sem_post(cfg->fork);
	sem_post(cfg->fork);
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

void	ft_routine(t_cfg *cfg, t_philo *philo)
{
	t_bool	sim;

	if (!ft_routine_init(cfg, philo))
		exit(1);
	sim = TRUE;
	while (sim)
	{
		if (philo->n_eat == cfg->n_eat)
			sem_post(cfg->full);
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
