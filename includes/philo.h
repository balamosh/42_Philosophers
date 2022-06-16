/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:56:21 by sotherys          #+#    #+#             */
/*   Updated: 2022/06/16 05:18:23 by sotherys         ###   ########.fr       */
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
	PH_TAKES_FORK,
	PH_EATING,
	PH_SLEEPING,
	PH_THINKING,
	PH_DEAD
}			t_state;

typedef struct s_philo
{
	int		id;
	t_state	state;
	long	t_last;
	long	t_start;
	long	t_die;
	long	t_eat;
	long	t_sleep;
	int		f1;
	int		f2;
	int		fork_cnt;
	int		curr_eat;
	int		n_eat;
}				t_philo;

typedef struct s_cfg
{
	pthread_t		*tid;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	generic_mutex;
	pthread_mutex_t	mutex_sim;
	pthread_mutex_t	mutex_print;
	int				*forks;
	t_bool			sim;
	t_bool			thread_cfg;
	int				n;
	int				i;
	long			t_start;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				n_eat;
}				t_cfg;

void	ft_philo(int ac, char **av);

long	ft_gettime(void);

void	*ft_routine(void *data);
void	ft_routine_init(t_philo *philo, t_cfg *cfg);
long	ft_routine_status(t_cfg *cfg, t_philo *philo);
t_bool	ft_routine_check_time(long t_start, long t_d);
void	ft_routine_take_fork(t_philo *philo, t_cfg *cfg, int fork);

t_bool	ft_routine_dead(t_philo *philo, t_cfg *cfg);
void	ft_routine_thinking(t_philo *philo, t_cfg *cfg);
void	ft_routine_eating(t_philo *philo, t_cfg *cfg);
void	ft_routine_sleeping(t_philo *philo, t_cfg *cfg);

#endif
