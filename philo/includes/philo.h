/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:56:21 by sotherys          #+#    #+#             */
/*   Updated: 2022/06/30 14:33:58 by sotherys         ###   ########.fr       */
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
	int				id;
	t_state			state;
	pthread_mutex_t	mutex;
	t_bool			sim;
	t_bool			pthread_error;
	long			t_last;
	int				f1;
	int				f2;
	int				n_eat;
}				t_philo;

typedef struct s_cfg
{
	pthread_t		*tid;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*time;
	pthread_mutex_t	take_fork;
	pthread_mutex_t	mutex;
	pthread_mutex_t	print;
	int				n;
	long			t_start;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	int				curr_eat;
	int				n_eat;
}				t_cfg;

void	ft_philo(int ac, char **av);

t_bool	ft_philo_parse(t_cfg *cfg, int ac, char **av);
t_bool	ft_philo_threads(t_cfg *cfg);
void	ft_philo_threads_join(t_cfg *cfg);
t_bool	ft_philo_init(t_cfg *cfg, int ac, char **av);
void	ft_routine_end(t_cfg *cfg);
void	ft_philo_destroy(t_cfg *cfg);

long	ft_gettime(void);

void	*ft_routine(void *data);
t_philo	*ft_routine_init(t_cfg *cfg);
long	ft_routine_status(t_cfg *cfg, t_philo *philo);
t_bool	ft_routine_check_time(long t_start, long t_d);
void	ft_routine_wait(t_philo *philo, long t_last, long t_d);

void	ft_routine_thinking(t_philo *philo, t_cfg *cfg);
void	ft_routine_take_fork(t_philo *philo, t_cfg *cfg);
void	ft_routine_eating(t_philo *philo, t_cfg *cfg);
void	ft_routine_sleeping(t_philo *philo, t_cfg *cfg);

#endif
