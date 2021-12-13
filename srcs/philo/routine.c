/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:33:19 by sotherys          #+#    #+#             */
/*   Updated: 2021/12/14 00:12:04 by sotherys         ###   ########.fr       */
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

	cfg = (t_cfg*)data;
	ft_philo_init(&philo, cfg);
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
