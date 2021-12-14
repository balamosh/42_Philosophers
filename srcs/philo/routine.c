/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:33:19 by sotherys          #+#    #+#             */
/*   Updated: 2021/12/14 04:12:01 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	ft_routine_sim(t_philo *philo, t_cfg *cfg)
{
	if (ft_check_time(philo->t_last, cfg->t_die))
	{
		philo->state = PH_DEAD;
		ft_routine_print_status(cfg->t_start, philo->id, "died");
		pthread_mutex_lock(&cfg->mutex);
		cfg->sim = FALSE;
		pthread_mutex_unlock(&cfg->mutex);
		return (FALSE);
	}
	return (TRUE);
}

void	ft_routine_thinking(t_philo *philo, t_cfg *cfg)
{
	pthread_mutex_lock(&cfg->mutex);
	if (cfg->forks[philo->id % cfg->n] && \
		cfg->forks[(philo->id) % cfg->n])
	{
		cfg->forks[philo->id % cfg->n] = FALSE;
		ft_routine_print_status(cfg->t_start, philo->id, "has taken a fork");
		cfg->forks[(philo->id) % cfg->n] = FALSE;
		ft_routine_print_status(cfg->t_start, philo->id, "has taken a fork");
		philo->state = PH_EATING;
		philo->t_last_eat =  ft_routine_print_status(cfg->t_start, philo->id, "is eating");
	}
	pthread_mutex_unlock(&cfg->mutex);
}

void	ft_routine_eating(t_philo *philo, t_cfg *cfg)
{
	if (!ft_routine_check_time(philo->t_last, cfg->t_eat))
		return ;
	pthread_mutex_lock(&cfg->mutex);
	cfg->forks[philo->id % cfg->n] = TRUE;
	cfg->forks[(philo->id) % cfg->n] = TRUE;
	pthread_mutex_unlock(&cfg->mutex);
	philo->state = PH_SLEEPING;
	philo->t_last_sleep = ft_routine_print_status(cfg->t_start, philo->id, "is sleeping");
	philo->t_last_eat = philo->t_last_sleep;
	++philo->n_eat;
}

void	ft_routine_sleeping(t_philo *philo, t_cfg *cfg)
{
	if (!ft_routine_check_time(philo->t_last, cfg->t_sleep))
		return ;
	philo->state = PH_THINKING;
	ft_routine_print_status(cfg->t_start, philo->id, "is thinking");
}

void	*ft_routine(void *data)
{
	t_cfg	*cfg;
	t_philo	philo;

	cfg = (t_cfg*)data;
	ft_routine_init(&philo, cfg);
	while (ft_routine_sim(&philo, cfg))
	{
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
