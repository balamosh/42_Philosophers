/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 06:20:09 by sotherys          #+#    #+#             */
/*   Updated: 2022/06/22 10:28:38 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_routine_check_dead(void *data)
{
	t_philo	*philo;
	t_cfg	*cfg;

	philo = (t_philo*)data;
	cfg = philo->cfg;
	while (TRUE)
	{
		pthread_mutex_lock(&philo->time_mutex);
		if (ft_routine_check_time(philo->t_last, cfg->t_die))
		{
			sem_wait(cfg->print);
			printf("%ld %d died\n", ft_gettime() - cfg->t_start, philo->id + 1);
			break ;
		}
		pthread_mutex_unlock(&philo->time_mutex);
		usleep(1);
	}
	sem_post(cfg->sim_exit);
	return (NULL);
}

t_bool	ft_routine_init(t_cfg *cfg, t_philo *philo)
{
	philo->cfg = cfg;
	philo->sim = TRUE;
	philo->t_last = cfg->t_start;
	philo->state = PH_TAKES_FORK;
	philo->n_eat = 0;
	if (pthread_mutex_init(&philo->sim_mutex, NULL) || \
		pthread_mutex_init(&philo->time_mutex, NULL) || \
		pthread_create(&philo->tid, NULL, &ft_routine_check_dead, philo))
		return (FALSE);
	return (TRUE);
}

long	ft_routine_status(t_cfg *cfg, t_philo *philo)
{
	static const char	*msg[5] = \
	{"has taken a fork", "is eating", "is sleeping", "is thinking", "died"};
	long				timestamp;

	sem_wait(cfg->print);
	timestamp = ft_gettime();
	printf("%ld %d %s\n", \
			timestamp - cfg->t_start, philo->id + 1, msg[philo->state]);
	sem_post(cfg->print);
	return (timestamp);
}

t_bool	ft_routine_check_time(long t_start, long t_d)
{
	long	elapsed;

	elapsed = ft_gettime() - t_start;
	return (elapsed >= t_d);
}

void	ft_routine_wait(t_philo *philo, long t_d)
{
	while (!ft_routine_check_time(philo->t_last, t_d))
		continue ;
}
