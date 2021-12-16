/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:56:21 by sotherys          #+#    #+#             */
/*   Updated: 2021/12/16 11:08:57 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include "libft.h"

typedef struct timeval	t_time;

typedef enum s_state
{
	PH_EATING,
	PH_SLEEPING,
	PH_THINKING,
	PH_DEAD
}			t_state;

typedef struct s_philo
{
	int		id;
	t_state	state;
	t_time	t_last;
	int		f1;
	int		f2;
	int		fork_cnt;
	int		n_eat;
}				t_philo;

typedef struct s_cfg
{
	pthread_t		*tid;
	pthread_mutex_t	*mutex;
	int				*forks;
	t_bool			sim;
	t_bool			thread_cfg;
	int				n;
	int				i;
	t_time			t_start;
	t_time			t_die;
	t_time			t_eat;
	t_time			t_sleep;
	int				n_eat;
}				t_cfg;

void	ft_philo(int ac, char **av);

t_time	ft_time(long n);

void	*ft_routine(void *data);
void	ft_routine_init(t_philo *philo, t_cfg *cfg);
t_time	ft_routine_status(t_time t_start, int id, const char *msg);
t_bool	ft_routine_check_time(t_time t_start, t_time t_d);
void	ft_routine_take_fork(t_philo *philo, t_cfg *cfg, int fork);

t_bool	ft_routine_dead(t_philo *philo, t_cfg *cfg);
void	ft_routine_thinking(t_philo *philo, t_cfg *cfg);
void	ft_routine_eating(t_philo *philo, t_cfg *cfg);
void	ft_routine_sleeping(t_philo *philo, t_cfg *cfg);

#endif
