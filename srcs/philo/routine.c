/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:33:19 by sotherys          #+#    #+#             */
/*   Updated: 2021/12/16 03:03:39 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	ft_routine_dead(t_philo *philo, t_cfg *cfg)
{
	if (!cfg->sim)
		return (TRUE);
	if (ft_routine_check_time(philo->t_last, cfg->t_die))
	{
		philo->state = PH_DEAD;
		ft_routine_status(cfg->t_start, philo->id, "died");
		cfg->sim = FALSE;
		return (TRUE);
	}
	return (FALSE);
}

void	ft_routine_thinking(t_philo *philo, t_cfg *cfg)
{
	if (philo->f1 == philo->f2)
		return ;
	ft_routine_take_fork(philo, cfg, philo->f1);
	ft_routine_take_fork(philo, cfg, philo->f2);
	if (philo->fork_cnt == 2)
	{
		ft_routine_status(cfg->t_start, philo->id, "has taken a fork");
		ft_routine_status(cfg->t_start, philo->id, "has taken a fork");
		philo->state = PH_EATING;
		philo->t_last = ft_routine_status(cfg->t_start, philo->id, "is eating");
	}
}

void	ft_routine_eating(t_philo *philo, t_cfg *cfg)
{
	if (!ft_routine_check_time(philo->t_last, cfg->t_eat))
		return ;
	cfg->forks[philo->f1] = TRUE;
	cfg->forks[philo->f2] = TRUE;
	philo->fork_cnt = 0;
	philo->state = PH_SLEEPING;
	philo->t_last = \
	ft_routine_status(cfg->t_start, philo->id, "is sleeping");
	++philo->n_eat;
}

void	ft_routine_sleeping(t_philo *philo, t_cfg *cfg)
{
	if (!ft_routine_check_time(philo->t_last, cfg->t_sleep))
		return ;
	philo->state = PH_THINKING;
	ft_routine_status(cfg->t_start, philo->id, "is thinking");
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
	pthread_detach(cfg->tid[philo.id]);
	return (NULL);
}
