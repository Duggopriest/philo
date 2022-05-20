/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:41:48 by jgobbett          #+#    #+#             */
/*   Updated: 2022/05/20 13:34:10 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_all *all, int pn, long *ded_time)
{
	long	t;
	long	eatting;

	t = get_time();
	all->philos[pn].bork = 0;
	all->philos[(pn + 1) % all->philo_num].bork = 0;
	shift(all);
	pthread_mutex_lock(&all->philos[pn].fork);
	pthread_mutex_lock(&all->philos[(pn + 1) % all->philo_num].fork);
	printf("	%lims	%i has taken a fork\n", get_time(), pn + 1);
	printf("	%lims	%i has taken a fork\n", get_time(), pn + 1);
	printf("	%lims	%i is eating\n", get_time(), pn + 1);
	eatting = all->philos[0].time_to_eat + get_time();
	if (*ded_time < get_time())
		philo_ded(pn, all);
	*ded_time = all->philos[pn].time_to_die + get_time();
	while (eatting > get_time())
		;
	all->philos[pn].times_eatin--;
	pthread_mutex_unlock(&all->philos[pn].fork);
	pthread_mutex_unlock(&all->philos[(pn + 1) % all->philo_num].fork);
	all->philos[pn].bork = 1;
	all->philos[(pn + 1) % all->philo_num].bork = 1;
	psleep(all, pn);
}

void	*phylo_run(t_philo *philos)
{
	int		pn;
	long	ded_time;
	t_all	*all;

	pn = philos->id;
	all = philos->all;
	ded_time = philos->time_to_die + get_time();
	while (!all->has_ded && philos->times_eatin != 0)
	{
		while (!all->has_ded)
		{
			if (ded_time < get_time())
				philo_ded(pn, all);
			if (pn == all->line[0] && philos->bork
				&& all->philos[(pn + 1) % all->philo_num].bork
				&& all->philo_num > 1)
				break ;
		}
		eat(all, pn, &ded_time);
	}
	return (NULL);
}

void	make_line(t_all *all)
{
	int	i;
	int	j;

	all->line = malloc(sizeof(int) * all->philo_num);
	i = 0;
	j = 0;
	while (i < all->philo_num)
	{
		all->line[j++] = i;
		i += 2;
	}
	i = 1;
	while (i < all->philo_num)
	{
		all->line[j++] = i;
		i += 2;
	}
}

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc < 5)
		return (0);
	all.philo_num = ft_atoi(argv[1]);
	all.philos = malloc(sizeof(t_philo) * all.philo_num);
	all.has_ded = 0;
	all.loaded = 1;
	make_line(&all);
	spawn_philos(argv, &all, argc);
	while (all.has_ded == 0)
		;
	usleep(10000);
}
