#include "philo.h"

t_bool	ft_routine_sim(t_philo *philo, t_cfg *cfg)
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
		return (FALSE);
	}
	return (TRUE);
}

void	ft_routine_thinking(t_philo *philo, t_cfg *cfg)
{
	t_time	tv;

	pthread_mutex_lock(&cfg->mutex);
	if (cfg->forks[philo->id % cfg->n] && \
		cfg->forks[(philo->id + 1) % cfg->n])
	{
		cfg->forks[philo->id % cfg->n] = FALSE;
		gettimeofday(&tv, NULL);
		printf("%ld %d has taken a fork\n", tv.tv_usec, philo->id + 1);
		cfg->forks[(philo->id + 1) % cfg->n] = FALSE;
		gettimeofday(&tv, NULL);
		printf("%ld %d has taken a fork\n", tv.tv_usec, philo->id + 1);
		philo->state = PH_EATING;
		gettimeofday(&tv, NULL);
		printf("%ld %d is eating\n", tv.tv_usec, philo->id + 1);
	}
	pthread_mutex_unlock(&cfg->mutex);
}

void	ft_routine_eating(t_philo *philo, t_cfg *cfg)
{
	t_time	tv;

	usleep(cfg->t_eat);
	pthread_mutex_lock(&cfg->mutex);
	cfg->forks[philo->id % cfg->n] = TRUE;
	cfg->forks[(philo->id + 1) % cfg->n] = TRUE;
	pthread_mutex_unlock(&cfg->mutex);
	philo->state = PH_SLEEPING;
	gettimeofday(&tv, NULL);
	printf("%ld %d is sleeping\n", tv.tv_usec, philo->id + 1);
	philo->ate = tv.tv_usec;
	++philo->n_eat;
}

void	ft_routine_sleeping(t_philo *philo, t_cfg *cfg)
{
	t_time	tv;

	usleep(cfg->t_sleep);
	gettimeofday(&tv, NULL);
	philo->state = PH_THINKING;
	printf("%ld %d is thinking\n", tv.tv_usec, philo->id + 1);
}
