/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:56:10 by sotherys          #+#    #+#             */
/*   Updated: 2021/12/16 01:50:07 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	ft_philo_parse(t_cfg *cfg, int ac, char **av)
{
	cfg->n = ft_atol(av[0]);
	cfg->t_die = ft_time(ft_atol(av[1]));
	cfg->t_eat = ft_time(ft_atol(av[2]));
	cfg->t_sleep = ft_time(ft_atol(av[3]));
	cfg->n_eat = -1;
	if (ac == 5)
		cfg->n_eat = ft_atol(av[4]);
	if (cfg->n < 0 || (cfg->n_eat < 0 && ac == 5))
		return (FALSE);
	return (TRUE);
}

static	t_bool	ft_philo_threads(t_cfg *cfg)
{
	int	i;

	i = 0;
	while (i < cfg->n)
		if (pthread_mutex_init(&cfg->mutex[i++], NULL))
			return (FALSE);
	i = 0;
	while (i < cfg->n)
		if (pthread_create(&cfg->tid[i++], NULL, &ft_routine, cfg))
			return (FALSE);
	return (TRUE);
}

static t_bool	ft_philo_init(t_cfg *cfg, int ac, char **av)
{
	t_time	tv;
	int		i;

	if (!ft_philo_parse(cfg, ac, av))
		return (FALSE);
	if (!(ft_malloc((void **)&cfg->tid, sizeof(pthread_t) * cfg->n) && \
		ft_malloc((void **)&cfg->forks, sizeof(t_bool) * cfg->n) && \
		ft_malloc((void **)&cfg->mutex, sizeof(pthread_mutex_t) * cfg->n)))
		return (FALSE);
	i = 0;
	while (i < cfg->n)
		cfg->forks[i++] = TRUE;
	cfg->sim = FALSE;
	ft_philo_threads(cfg);
	gettimeofday(&tv, NULL);
	cfg->t_start = tv;
	cfg->sim = TRUE;
	return (TRUE);
}

static void	ft_philo_destroy(t_cfg *cfg)
{
	int	i;

	i = 0;
	while (i < cfg->n)
		pthread_mutex_destroy(&cfg->mutex[i++]);
}

void	ft_philo(int ac, char **av)
{
	t_cfg	cfg;

	if (!ft_philo_init(&cfg, ac, av))
		return ;
	while (cfg.sim)
		continue ;
	cfg.i = 0;
	while (cfg.i < cfg.n)
		pthread_join(cfg.tid[cfg.i++], NULL);
	ft_philo_destroy(&cfg);
}
