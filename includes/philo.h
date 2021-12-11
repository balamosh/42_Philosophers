/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotherys <sotherys@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:56:21 by sotherys          #+#    #+#             */
/*   Updated: 2021/12/11 16:14:08 by sotherys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include "libft.h"

typedef struct s_philo
{
	pthread_t	*tid;
	t_bool		*forks;
	t_bool		sim;
	int			n;
	long		t_die;
	long		t_eat;
	long		t_sleep;
	int			n_eat;
}				t_philo;

#endif
