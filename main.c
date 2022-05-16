/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 17:22:15 by marvin            #+#    #+#             */
/*   Updated: 2022/05/15 17:22:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//inislize at start then call anywhere with printf_time(NULL)
void	printf_time(void)
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
		printf("%ld\n", (end.tv_sec * 1000000 + end.tv_usec)
			- (start->tv_sec * 1000000 + start->tv_usec));
	}
}

void	*phylo_run(void *vargp)
{
	if (!vargp)
		sleep(1);
	sleep(3);
	printf_time();
	return (NULL);
}

void	spawn_philos(char **argv, t_all *all)
{
	int	i;

	all->thread_id = malloc(sizeof(pthread_t) * all->forks);
	i = -1;
	while (++i < all->forks)
	{
		all->philos[i].time_to_die = ft_atoi(argv[1]);
		pthread_create(&all->thread_id[0], NULL, phylo_run, NULL);
	}
	i = -1;
	while (++i < all->forks)
		all->philos[i].time_to_die = ft_atoi(argv[2]);
	i = -1;
	while (++i < all->forks)
		all->philos[i].time_to_die = ft_atoi(argv[3]);
}

void	run_threads(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->forks)
		pthread_join(all->thread_id[i], NULL);
}

int	main(int argc, char	**argv)
{
	t_all	all;

	printf_time();
	all.forks = argc - 1;
	all.forks = 10;
	all.philo_num = all.forks;
	all.philos = malloc(sizeof(t_philo) * all.forks);
	spawn_philos(argv, &all);
	run_threads(&all);
}