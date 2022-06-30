/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 04:55:07 by sotherys          #+#    #+#             */
/*   Updated: 2022/06/30 19:03:16 by sotherys         ###   ########.fr       */
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
	if (cfg->n <= 0 || cfg->t_die <= 0 || \
		cfg->t_eat <= 0 || cfg->t_sleep <= 0 || \
		(cfg->n_eat <= 0 && ac == 5))
		return (FALSE);
	return (TRUE);
}

t_bool	ft_philo_fork_create(t_cfg *cfg)
{
	t_philo	philo;
	int		i;

	i = 0;
	while (i < cfg->n)
	{
		cfg->child[i] = fork();
		if (cfg->child[i] == 0)
		{
			philo.id = i;
			ft_routine(cfg, &philo);
			exit(0);
		}
		else if (cfg->child[i] < 0)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

void	ft_philo_fork_kill(t_cfg *cfg)
{
	int	i;

	i = 0;
	while (i < cfg->n)
	{
		sem_post(cfg->full);
		if (cfg->child[i] > 0)
			kill(cfg->child[i], SIGKILL);
		++i;
	}
}
