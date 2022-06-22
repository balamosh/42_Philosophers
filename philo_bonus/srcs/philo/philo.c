/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:56:10 by sotherys          #+#    #+#             */
/*   Updated: 2022/06/22 19:28:16 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_philo_check_full(void *data)
{
	t_cfg	*cfg;
	int		i;
	t_bool	sim;

	cfg = (t_cfg *)data;
	if (cfg->n_eat < 0)
		return (NULL);
	i = 0;
	while (TRUE)
	{
		sem_wait(cfg->full);
		pthread_mutex_lock(&cfg->mutex);
		sim = cfg->sim;
		pthread_mutex_unlock(&cfg->mutex);
		if (++i == cfg->n || !sim)
			break ;
		sem_post(cfg->print);
	}
	sem_post(cfg->sim_exit);
	return (NULL);
}

t_bool	ft_philo_init(t_cfg *cfg, int ac, char **av)
{
	if (!(ft_philo_parse(cfg, ac, av) && \
		ft_malloc((void **)&cfg->child, sizeof(pid_t) * cfg->n) && \
		!pthread_mutex_init(&cfg->mutex, NULL)))
		return (FALSE);
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/full");
	sem_unlink("/sim_exit");
	cfg->fork = sem_open("/fork", O_CREAT, 0, cfg->n);
	cfg->print = sem_open("/print", O_CREAT, 0, 1);
	cfg->full = sem_open("/full", O_CREAT, 0, 0);
	cfg->sim_exit = sem_open("/sim_exit", O_CREAT, 0, 0);
	if (SEM_FAILED == cfg->fork || \
		SEM_FAILED == cfg->print || \
		SEM_FAILED == cfg->full || \
		SEM_FAILED == cfg->sim_exit)
		return (FALSE);
	cfg->sim = TRUE;
	cfg->t_start = ft_gettime();
	cfg->curr_eat = 0;
	return (TRUE);
}

void	ft_philo(int ac, char **av)
{
	t_cfg	cfg;
	t_philo	philo;
	int		i;

	if (!ft_philo_init(&cfg, ac, av))
		return ;
	i = 0;
	while (i < cfg.n)
	{
		cfg.child[i] = fork();
		if (cfg.child[i] == 0)
		{
			philo.id = i;
			ft_routine(&cfg, &philo);
			return ;
		}
		++i;
	}
	pthread_create(&cfg.full_tid, NULL, &ft_philo_check_full, &cfg);
	//pthread_detach(cfg.full_tid);
	sem_wait(cfg.sim_exit);
	pthread_mutex_lock(&cfg.mutex);
	cfg.sim = FALSE;
	pthread_mutex_unlock(&cfg.mutex);
	i = 0;
	while (i < cfg.n)
	{
		sem_post(cfg.full);
		kill(cfg.child[i], SIGKILL);
		++i;
	}
	pthread_join(cfg.full_tid, NULL);
	ft_philo_destroy(&cfg);
}
