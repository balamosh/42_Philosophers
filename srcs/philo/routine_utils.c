#include "philo.h"

t_bool	ft_routine_dead(t_philo *philo, t_cfg *cfg)
{
	t_time	tv;

	gettimeofday(&tv, NULL);
	if (tv.tv_usec - philo->ate >= cfg->t_die)
	{
		philo->state = PH_DEAD;
		printf("%ld %d died\n", tv.tv_usec, philo->id + 1);
		pthread_mutex_lock(&cfg->mutex);
		cfg->sim = FALSE;
		pthread_mutex_unlock(&cfg->mutex);
		return (TRUE);
	}
	return (FALSE);
}
