/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:18:50 by jgobbett          #+#    #+#             */
/*   Updated: 2022/05/18 17:36:16 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	int_ods(char **argv, t_all *all)
{
	int	i;

	i = 1;
	while (++i < all->philo_num)
	{
		all->philos[i].id = i;
		all->philos[i].bork = 1;
		all->philos[i].all = all;
		all->philos[i].times_eatin = -1;
		all->philos[i].time_to_die = ft_atoi(argv[2]);
		all->philos[i].time_to_eat = ft_atoi(argv[3]);
		all->philos[i].time_to_sleep = ft_atoi(argv[4]);
		pthread_create(&all->thread_id[i], NULL,
			(void *_Nullable)phylo_run, &all->philos[i]);
		pthread_mutex_init(&all->philos[i].fork, NULL);
		i += 2;
	}
}

void	spawn_philos(char **argv, t_all *all, int argc)
{
	int	i;

	all->thread_id = malloc(sizeof(pthread_t) * all->philo_num);
	i = -1;
	while (++i < all->philo_num)
	{
		all->philos[i].id = i;
		all->philos[i].bork = 1;
		all->philos[i].all = all;
		all->philos[i].times_eatin = -1;
		all->philos[i].time_to_die = ft_atoi(argv[2]);
		all->philos[i].time_to_eat = ft_atoi(argv[3]);
		all->philos[i].time_to_sleep = ft_atoi(argv[4]);
		pthread_create(&all->thread_id[i], NULL,
			(void *_Nullable)phylo_run, &all->philos[i]);
		pthread_mutex_init(&all->philos[i].fork, NULL);
		i += 2;
	}
	int_ods(argv, all);
	if (argc == 6)
		while (++i < all->philo_num)
			all->philos[i].times_eatin = ft_atoi(argv[5]);
}

void	run_threads(t_all *all)
{
	int	i;

	i = 0;
	get_time();
	while (i < all->philo_num)
	{
		pthread_join(all->thread_id[i], NULL);
		i += 2;
	}
	i = 1;
	while (i < all->philo_num)
	{
		pthread_join(all->thread_id[i], NULL);
		i += 2;
	}
}

void	philo_ded(int i, t_all *all)
{
	int	j;

	all->has_ded = 1;
	printf("	%lims	%i died\n", get_time(), i + 1);
	j = -1;
	while (++j <= all->philo_num)
		pthread_detach(all->thread_id[i]);
	exit(0);
}

void	psleep(t_all *all, int i)
{
	long	wake_up;

	if (all->has_ded == 0)
	{
		printf("	%lims	%i is sleeping\n", get_time(), i + 1);
		wake_up = all->philos[i].time_to_sleep + get_time();
		while (wake_up >= get_time() && all->has_ded == 0)
			get_time();
	}
}
