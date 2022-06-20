/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:56:10 by sotherys          #+#    #+#             */
/*   Updated: 2022/06/20 15:31:40 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
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
*/

static void	*ft_philo_check_dead(void *data)
{
	t_cfg	*cfg;
	int		i;

	cfg = (t_cfg *)data;
	if (cfg->n_eat < 0)
		return (NULL);
	i = 0;
	while (i < cfg->n)
	{
		sem_wait(cfg->full);
		printf("%d IS FULL\n", i);
	}
	return (NULL);
}

void	ft_philo(int ac, char **av)
{
	t_cfg	cfg;
	t_philo	philo;
	int		i;

	if (!ft_philo_parse(&cfg, ac, av))
		return ;
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/full");
	cfg.fork = sem_open("/fork", O_CREAT, 0, cfg.n);
	cfg.print = sem_open("/print", O_CREAT, 0, 1);
	cfg.full = sem_open("/full", O_CREAT, 0, 0);
	if (SEM_FAILED == cfg.fork)
	{
		printf("SEM FAILED\n");
		printf("ERROR = %d\n", errno);
	}
	cfg.t_start = ft_gettime();
	cfg.curr_eat = 0;
	i = 0;
	while (i < cfg.n)
	{
		if (fork() == 0)
		{
			philo.id = i;
			ft_routine(&cfg, &philo);
			return ;
		}
		++i;
	}
	pthread_create(&cfg.dead_id, NULL, &ft_philo_check_dead, NULL);
	waitpid(-1, 0, 0);
	i = 0;
	while (i < cfg.n)
		sem_post(cfg.full);
	pthread_join(cfg.dead_id, NULL);
	exit(0);
	//ft_philo_destroy(&cfg);
}
