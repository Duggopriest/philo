/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:18:50 by jgobbett          #+#    #+#             */
/*   Updated: 2022/05/17 13:00:41 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	spawn_philos(char **argv, t_all *all)
{
	int	i;

	printf("spawning %i philos\n", all->philo_num);
	all->thread_id = malloc(sizeof(pthread_t) * all->philo_num);
	i = -1;
	while (++i < all->philo_num)
	{
		all->philos[i].time_to_die = ft_atoi(argv[2]);
		all->philos[i].time_to_eat = ft_atoi(argv[3]);
		all->philos[i].time_to_sleep = ft_atoi(argv[4]);
		pthread_create(&all->thread_id[i], NULL, phylo_run, all);
	}
}

void	run_threads(t_all *all)
{
	int	i;

	i = -1;
	printf_time();
	get_time();
	while (++i < all->philo_num)
		pthread_join(all->thread_id[i], NULL);
}

void	philo_ded(int i, t_all *all)
{
	int	j;

	all->has_ded = 1;
	printf("	%lims	%i died\n", get_time(), i);
	j = -1;
	while (++j <= all->philo_num)
		pthread_detach(all->thread_id[i]);
	exit(0);
}
