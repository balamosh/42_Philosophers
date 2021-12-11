/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:56:10 by sotherys          #+#    #+#             */
/*   Updated: 2021/12/11 16:00:51 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_parse(t_philo *tab, int ac, char **av)
{
	tab->n = ft_atoi(av[0]);
	tab->t_die = ft_atoi(av[1]);
	tab->t_eat = ft_atoi(av[2]);
	tab->t_sleep = ft_atoi(av[3]);
	tab->n_eat = -1;
	if (ac == 5)
		tab->n_eat = ft_atoi(av[4]);
	
}

void	ft_philo(int ac, char **av)
{
	t_philo	tab;

	
}
