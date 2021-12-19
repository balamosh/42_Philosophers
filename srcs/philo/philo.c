/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:56:10 by sotherys          #+#    #+#             */
/*   Updated: 2021/12/19 07:06:41 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	ft_philo_parse(t_cfg *cfg, int ac, char **av)
{
	cfg->n = ft_atol(av[0]);
	cfg->t_die = ft_atol(av[1]);
	cfg->t_eat = ft_atol(av[2]);
	cfg->t_sleep = ft_atol(av[3]);
	cfg->n_eat = -1;
	if (ac == 5)
		cfg->n_eat = ft_atol(av[4]);
	if (cfg->n < 0 || cfg->t_die < 0 || cfg->t_eat < 0 || cfg->t_sleep < 0 || \
		(cfg->n_eat < 0 && ac == 5))
		return (FALSE);
	return (TRUE);
}

static t_bool	ft_philo_threads(t_cfg *cfg)
{
	int	i;

	i = 0;
	while (i < cfg->n)
		if (pthread_mutex_init(&cfg->mutex[i++], NULL))
			return (FALSE);
	if (pthread_mutex_init(&cfg->generic_mutex, NULL))
		return (FALSE);
	if (pthread_mutex_init(&cfg->mutex_sim, NULL))
		return (FALSE);
	i = 0;
	while (i < cfg->n)
		if (pthread_create(&cfg->tid[i++], NULL, &ft_routine, cfg))
			return (FALSE);
	return (TRUE);
}

static t_bool	ft_philo_init(t_cfg *cfg, int ac, char **av)
{
	int		i;

	if (!ft_philo_parse(cfg, ac, av))
		return (FALSE);
	if (!(ft_malloc((void **)&cfg->tid, sizeof(pthread_t) * cfg->n) && \
		ft_malloc((void **)&cfg->forks, sizeof(int) * cfg->n) && \
		ft_malloc((void **)&cfg->mutex, sizeof(pthread_mutex_t) * cfg->n)))
		return (FALSE);
	i = 0;
	while (i < cfg->n)
		cfg->forks[i++] = -1;
	cfg->sim = FALSE;
	ft_philo_threads(cfg);
	cfg->t_start = ft_gettime();
	cfg->sim = TRUE;
	pthread_mutex_lock(&cfg->mutex_sim);
	return (TRUE);
}

static void	ft_philo_destroy(t_cfg *cfg)
{
	int	i;

	i = 0;
	while (i < cfg->n)
		pthread_mutex_destroy(&cfg->mutex[i++]);
	pthread_mutex_destroy(&cfg->generic_mutex);
	pthread_mutex_destroy(&cfg->mutex_sim);
}

void	ft_philo(int ac, char **av)
{
	t_cfg	cfg;

	if (!ft_philo_init(&cfg, ac, av))
		return ;
	while (cfg.sim)
		continue ;
	pthread_mutex_lock(&cfg.generic_mutex);
	/*
	cfg.i = 0;
	while (cfg.i < cfg.n)
		pthread_join(cfg.tid[cfg.i++], NULL);
	*/
	pthread_mutex_lock(&cfg.mutex_sim);
	ft_philo_destroy(&cfg);
}
