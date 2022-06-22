/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 04:55:07 by sotherys          #+#    #+#             */
/*   Updated: 2022/06/22 19:35:13 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	ft_philo_parse(t_cfg *cfg, int ac, char **av)
{
	cfg->n = ft_atol(av[0]);
	cfg->t_die = ft_atol(av[1]);
	cfg->t_eat = ft_atol(av[2]);
	cfg->t_sleep = ft_atol(av[3]);
	cfg->n_eat = -1;
	if (ac == 5)
		cfg->n_eat = ft_atol(av[4]);
	if (cfg->n < 0 || cfg->t_die < 0 || cfg->t_eat < 0 || cfg->t_sleep < 0 || \
		(cfg->n_eat <= 0 && ac == 5))
		return (FALSE);
	return (TRUE);
}

/*
t_bool	ft_philo_threads(t_cfg *cfg)
{
	int	i;

	i = 0;
	while (i < cfg->n)
	{
		if (pthread_mutex_init(&cfg->fork[i], NULL) || \
			pthread_mutex_init(&cfg->time[i], NULL) || \
			pthread_mutex_init(&cfg->philo[i].mutex, NULL))
			return (FALSE);
		cfg->philo[i].t_last = cfg->t_start;
		cfg->philo[i].id = i;
		cfg->philo[i].sim = TRUE;
		++i;
	}
	i = 0;
	while (i < cfg->n)
	{
		if (pthread_create(&cfg->tid[i], NULL, &ft_routine, cfg))
			return (FALSE);
		++i;
	}
	return (TRUE);
}

t_bool	ft_philo_init(t_cfg *cfg, int ac, char **av)
{
	if (!ft_philo_parse(cfg, ac, av))
		return (FALSE);
	if (!(!pthread_mutex_init(&cfg->mutex, NULL) && \
		!pthread_mutex_init(&cfg->print, NULL) && \
		ft_malloc((void **)&cfg->tid, sizeof(pthread_t) * cfg->n) && \
		ft_malloc((void **)&cfg->philo, sizeof(t_philo) * cfg->n) && \
		ft_malloc((void **)&cfg->fork, sizeof(pthread_mutex_t) * cfg->n) && \
		ft_malloc((void **)&cfg->time, sizeof(pthread_mutex_t) * cfg->n)))
		return (FALSE);
	cfg->t_start = ft_gettime();
	cfg->curr_eat = 0;
	ft_philo_threads(cfg);
	return (TRUE);
}
*/

void	ft_philo_destroy(t_cfg *cfg)
{
	pthread_mutex_destroy(&cfg->mutex);
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/full");
	sem_unlink("/sim_exit");
	sem_close(cfg->fork);
	sem_close(cfg->print);
	sem_close(cfg->full);
	sem_close(cfg->sim_exit);
	free(cfg->child);
}