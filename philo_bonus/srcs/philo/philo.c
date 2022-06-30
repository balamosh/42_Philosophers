/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:56:10 by sotherys          #+#    #+#             */
/*   Updated: 2022/06/30 19:05:38 by sotherys         ###   ########.fr       */
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

static void	ft_philo_sem_unlink(void)
{
	sem_unlink("/fork");
	sem_unlink("/take_fork");
	sem_unlink("/print");
	sem_unlink("/full");
	sem_unlink("/sim_exit");
}

t_bool	ft_philo_init(t_cfg *cfg, int ac, char **av)
{
	cfg->child = NULL;
	cfg->fork = SEM_FAILED;
	cfg->take_fork = SEM_FAILED;
	cfg->print = SEM_FAILED;
	cfg->full = SEM_FAILED;
	cfg->sim_exit = SEM_FAILED;
	if (!(ft_philo_parse(cfg, ac, av) && \
		ft_calloc((void **)&cfg->child, sizeof(pid_t) * cfg->n) && \
		!pthread_mutex_init(&cfg->mutex, NULL)))
		return (FALSE);
	ft_philo_sem_unlink();
	cfg->fork = sem_open("/fork", O_CREAT, 0, cfg->n);
	cfg->take_fork = sem_open("/take_fork", O_CREAT, 0, 1);
	cfg->print = sem_open("/print", O_CREAT, 0, 1);
	cfg->full = sem_open("/full", O_CREAT, 0, 0);
	cfg->sim_exit = sem_open("/sim_exit", O_CREAT, 0, 0);
	if (SEM_FAILED == cfg->fork || SEM_FAILED == cfg->print || \
		SEM_FAILED == cfg->full || SEM_FAILED == cfg->sim_exit || \
		SEM_FAILED == cfg->take_fork)
		return (FALSE);
	cfg->sim = TRUE;
	cfg->t_start = ft_gettime();
	cfg->curr_eat = 0;
	return (TRUE);
}

void	ft_philo_destroy(t_cfg *cfg)
{
	ft_philo_sem_unlink();
	sem_close(cfg->fork);
	sem_close(cfg->take_fork);
	sem_close(cfg->print);
	sem_close(cfg->full);
	sem_close(cfg->sim_exit);
	free(cfg->child);
}

void	ft_philo(int ac, char **av)
{
	t_cfg	cfg;

	if (!ft_philo_init(&cfg, ac, av))
		return (ft_philo_destroy(&cfg));
	if (!ft_philo_fork_create(&cfg))
		return (ft_philo_fork_kill(&cfg));
	pthread_create(&cfg.full_tid, NULL, &ft_philo_check_full, &cfg);
	sem_wait(cfg.sim_exit);
	pthread_mutex_lock(&cfg.mutex);
	cfg.sim = FALSE;
	pthread_mutex_unlock(&cfg.mutex);
	ft_philo_fork_kill(&cfg);
	pthread_join(cfg.full_tid, NULL);
	ft_philo_destroy(&cfg);
}
