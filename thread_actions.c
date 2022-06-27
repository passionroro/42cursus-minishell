/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:25:03 by henkaoua          #+#    #+#             */
/*   Updated: 2022/03/30 15:55:13 by henkaoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	zzz(t_individual *i, size_t t)
{
	size_t	s;

	s = get_time();
	while (monitor(i))
	{
		if ((get_time() - s) > t)
			break ;
		usleep(150);
	}
}

int	monitor(t_individual *i)
{
	pthread_mutex_lock(&i->g->lock);
	if ((get_time() - i->last_eat) > i->g->to_die && i->g->alive)
	{
		printf("%ld %d died\n", get_time(), i->id);
		i->g->alive = 0;
		pthread_mutex_unlock(&i->g->lock);
		return (0);
	}
	pthread_mutex_unlock(&i->g->lock);
	return (1 && i->g->alive);
}

int	take_fork(t_individual *i)
{
	pthread_mutex_lock(&i->lock);
	if (monitor(i))
		printf("%ld %d has taken a fork\n", get_time(), i->id);
	pthread_mutex_lock(&i->next->lock);
	if (!monitor(i))
		return (0);
	printf("%ld %d is eating\n", get_time(), i->id);
	i->last_eat = get_time();
	zzz(i, i->g->to_eat);
	pthread_mutex_unlock(&i->next->lock);
	pthread_mutex_unlock(&i->lock);
	i->num_eaten += 1;
	return (1);
}

void	*routine(void *arg)
{
	t_individual	*i;

	i = (t_individual *)arg;
	if (i->id % 2)
		usleep(150);
	while (1)
	{
		if (monitor(i))
			take_fork(i);
		else
			return (NULL);
		if (i->num_eaten == i->g->must_eat)
			return (NULL);
		if (monitor(i))
		{
			printf("%ld %d is sleeping\n", get_time(), i->id);
			zzz(i, i->g->to_sleep);
		}
		if (monitor(i))
			printf("%ld %d is thinking\n", get_time(), i->id);
	}
	return (NULL);
}
