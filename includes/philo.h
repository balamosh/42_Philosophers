/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:56:21 by sotherys          #+#    #+#             */
/*   Updated: 2021/12/14 00:12:20 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include "libft.h"

typedef struct timeval t_time;

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
	long	ate;
	int		n_eat;
}				t_philo;

typedef struct s_cfg
{
	pthread_t		*tid;
	pthread_mutex_t	mutex;
	t_bool			*forks;
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
void	*ft_routine(void *data);
t_bool	ft_routine_sim(t_philo *philo, t_cfg *cfg);
void	ft_routine_thinking(t_philo *philo, t_cfg *cfg);
void	ft_routine_eating(t_philo *philo, t_cfg *cfg);
void	ft_routine_sleeping(t_philo *philo, t_cfg *cfg);

#endif
