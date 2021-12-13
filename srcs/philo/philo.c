/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:56:10 by sotherys          #+#    #+#             */
/*   Updated: 2021/12/13 22:06:08 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	ft_philo_parse(t_cfg *cfg, int ac, char **av)
{
	t_time	tv;
	int		i;

	gettimeofday(&tv, NULL);
	cfg->t_start = tv.tv_usec;
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
	if (!(ft_malloc((void **)&cfg->tid, sizeof(pthread_t) * cfg->n) && \
			ft_malloc((void **)&cfg->forks, sizeof(t_bool) * cfg->n)))
		return (FALSE);
	i = 0;
	while (i < cfg->n)
		cfg->forks[i++] = TRUE;
	return (TRUE);
}

void	ft_philo(int ac, char **av)
{
	t_cfg	cfg;

	ft_philo_parse(&cfg, ac, av);
	if (pthread_mutex_init(&cfg.mutex, NULL))
		return ;
	cfg.i = 0;
	while (cfg.i < cfg.n)
	{
		cfg.thread_cfg = FALSE;
		if (pthread_create(&cfg.tid[cfg.i], NULL, &ft_routine, &cfg))
			return ;
		while (!cfg.thread_cfg)
			continue ;
		++cfg.i;
	}
	while (cfg.sim)
		continue ;
	cfg.i = 0;
	while (cfg.i < cfg.n)
		pthread_join(cfg.tid[cfg.i++], NULL);
	pthread_mutex_destroy(&cfg.mutex);
}
