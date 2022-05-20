/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:47:56 by jgobbett          #+#    #+#             */
/*   Updated: 2022/05/20 13:33:22 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	spawn_philos(char **argv, t_all *all, int argc)
{
	int	i;

	all->thread_id = malloc(sizeof(pthread_t) * all->philo_num);
	i = -1;
	while (++i < all->philo_num)
	{
		all->philos[i].id = i;
		all->philos[i].all = all;
		all->philos[i].times_eatin = -1;
		all->philos[i].time_to_die = ft_atoi(argv[2]);
		all->philos[i].time_to_eat = ft_atoi(argv[3]);
		all->philos[i].time_to_sleep = ft_atoi(argv[4]);
		pthread_create(&all->thread_id[i], NULL,
			(void *)phylo_run, &all->philos[i]);
		pthread_mutex_init(&all->philos[i].fork, NULL);
		all->philos[i].bork = 1;
	}
	i = -1;
	if (argc == 6)
		while (++i < all->philo_num)
			all->philos[i].times_eatin = ft_atoi(argv[5]);
	get_time();
	all->loaded = 0;
}

long	get_time(void)
{
	struct timeval			end;
	static struct timeval	*start = NULL;

	if (start == NULL)
	{
		start = malloc(sizeof(end));
		gettimeofday(start, NULL);
	}
	else
	{
		gettimeofday(&end, NULL);
		return (((end.tv_sec) * 1000 + (end.tv_usec) / 1000)
			- ((start->tv_sec) * 1000 + (start->tv_usec) / 1000));
	}
	return (0);
}

void	shift(t_all *all)
{
	int	i;
	int	temp;
	int	len;

	len = all->philo_num - 1;
	temp = all->line[0];
	i = -1;
	while (++i < len)
		all->line[i] = all->line[i + 1];
	all->line[len] = temp;
}

void	philo_ded(int i, t_all *all)
{
	int	j;

	all->has_ded = 1;
	printf("	%lims	%i died\n", get_time(), i + 1);
	j = -1;
	while (++j <= all->philo_num)
		pthread_detach(all->thread_id[j]);
}

void	psleep(t_all *all, int pn)
{
	long	tsleep;
	long	t;

	if (all->has_ded == 0)
	{
		t = get_time();
		tsleep = all->philos[pn].time_to_sleep + t;
		printf("	%lims	%i is sleeping\n", t, pn + 1);
		while (tsleep > get_time())
			;
		if (!all->has_ded)
			printf("	%lims	%i is thinking\n",
				t + all->philos[pn].time_to_sleep, pn + 1);
	}
}
