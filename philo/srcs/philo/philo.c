/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:56:10 by sotherys          #+#    #+#             */
/*   Updated: 2022/06/20 00:42:38 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_routine_end(t_cfg *cfg)
{
	int	i;

	i = 0;
	while (i < cfg->n)
	{
		pthread_mutex_lock(&cfg->philo[i].mutex);
		cfg->philo[i].sim = FALSE;
		pthread_mutex_unlock(&cfg->philo[i].mutex);
		++i;
	}
}

static t_bool	ft_philo_check_dead(t_philo *philo, t_cfg *cfg)
{
	t_bool	ret;

	ret = FALSE;
	pthread_mutex_lock(&cfg->time[philo->id]);
	if (ft_routine_check_time(philo->t_last, cfg->t_die))
	{
		pthread_mutex_lock(&cfg->print);
		printf("%ld %d died\n", ft_gettime() - cfg->t_start, philo->id + 1);
		ft_routine_end(cfg);
		pthread_mutex_unlock(&cfg->print);
		ret = TRUE;
	}
	pthread_mutex_unlock(&cfg->time[philo->id]);
	return (ret);
}

static t_bool	ft_philo_check_full(t_cfg *cfg)
{
	t_bool	ret;

	ret = FALSE;
	pthread_mutex_lock(&cfg->mutex);
	if (cfg->curr_eat == cfg->n)
	{
		pthread_mutex_lock(&cfg->print);
		ft_routine_end(cfg);
		pthread_mutex_unlock(&cfg->print);
		ret = TRUE;
	}
	pthread_mutex_unlock(&cfg->mutex);
	return (ret);
}

void	ft_philo(int ac, char **av)
{
	t_cfg	cfg;
	int		i;
	t_bool	sim;

	if (!ft_philo_init(&cfg, ac, av))
		return ;
	sim = TRUE;
	while (sim)
	{
		i = 0;
		while (i < cfg.n)
		{
			if (ft_philo_check_full(&cfg) || \
				ft_philo_check_dead(&cfg.philo[i++], &cfg))
			{
				sim = FALSE;
				break ;
			}
		}
	}
	i = 0;
	while (i < cfg.n)
		pthread_join(cfg.tid[i++], NULL);
	ft_philo_destroy(&cfg);
}
