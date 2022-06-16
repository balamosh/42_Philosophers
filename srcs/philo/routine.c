/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:33:19 by sotherys          #+#    #+#             */
/*   Updated: 2022/06/16 05:18:42 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	ft_routine_dead(t_philo *philo, t_cfg *cfg)
{
	t_bool	ret;

	ret = FALSE;
	if (ft_routine_check_time(philo->t_last, philo->t_die))
	{
		philo->state = PH_DEAD;
		ft_routine_status(cfg, philo);
		ret = TRUE;
	}
	pthread_mutex_lock(&cfg->mutex_sim);
	//pthread_mutex_lock(&cfg->generic_mutex);
	if (!cfg->sim)
		ret = TRUE;
	//pthread_mutex_unlock(&cfg->generic_mutex);
	pthread_mutex_unlock(&cfg->mutex_sim);
	return (ret);
}

void	ft_routine_thinking(t_philo *philo, t_cfg *cfg)
{
	if (philo->f1 == philo->f2)
		return ;
	ft_routine_take_fork(philo, cfg, philo->f1);
	ft_routine_take_fork(philo, cfg, philo->f2);
	if (philo->fork_cnt == 2)
	{
		philo->state = PH_TAKES_FORK;
		ft_routine_status(cfg, philo);
		ft_routine_status(cfg, philo);
		philo->state = PH_EATING;
		philo->t_last = ft_routine_status(cfg, philo);
	}
	else
	{
		//pthread_mutex_lock(&cfg->generic_mutex);
		pthread_mutex_lock(&cfg->mutex[philo->f1]);
		if (cfg->forks[philo->f1] == philo->id)
			cfg->forks[philo->f1] = -1;
		pthread_mutex_unlock(&cfg->mutex[philo->f1]);
		pthread_mutex_lock(&cfg->mutex[philo->f2]);
		if (cfg->forks[philo->f2] == philo->id)
			cfg->forks[philo->f2] = -1;
		pthread_mutex_unlock(&cfg->mutex[philo->f2]);
		//pthread_mutex_unlock(&cfg->generic_mutex);
		philo->fork_cnt = 0;
	}
}

void	ft_routine_eating(t_philo *philo, t_cfg *cfg)
{
	while (!ft_routine_check_time(philo->t_last, philo->t_eat))
		continue ;
	philo->state = PH_SLEEPING;
	philo->t_last = ft_routine_status(cfg, philo);
	pthread_mutex_lock(&cfg->mutex[philo->f1]);
	cfg->forks[philo->f1] = -1;
	pthread_mutex_unlock(&cfg->mutex[philo->f1]);
	pthread_mutex_lock(&cfg->mutex[philo->f2]);
	cfg->forks[philo->f2] = -1;
	pthread_mutex_unlock(&cfg->mutex[philo->f2]);
	philo->fork_cnt = 0;
	++philo->curr_eat;
}

void	ft_routine_sleeping(t_philo *philo, t_cfg *cfg)
{
	if (!ft_routine_check_time(philo->t_last, philo->t_sleep))
			return ;
	philo->state = PH_THINKING;
	ft_routine_status(cfg, philo);
}

void	*ft_routine(void *data)
{
	t_cfg	*cfg;
	t_philo	philo;

	cfg = (t_cfg *)data;
	ft_routine_init(&philo, cfg);
	while (TRUE)
	{
		if (ft_routine_dead(&philo, cfg))
			break ;
		if (philo.state == PH_THINKING)
			ft_routine_thinking(&philo, cfg);
		else if (philo.state == PH_EATING)
			ft_routine_eating(&philo, cfg);
		else if (philo.state == PH_SLEEPING)
			ft_routine_sleeping(&philo, cfg);
	}
	return (NULL);
}
