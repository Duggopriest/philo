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
int	check_eat(t_all *all)
{
	int	i;

	i = -1;
	while (i < all->philo_num)
		if (all->philos[i].times_eatin > 0
			|| all->philos[i].times_eatin < 0)
			return (1);
	return (0);
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

void	eat(t_all *all, int i, long *ded_time)
{
	long	t;
	//long	eatting;

	t = get_time();
	pthread_mutex_lock(&all->philos[i].fork);
	all->philos[i].bork = 0;
	pthread_mutex_lock(&all->philos[(i + 1) % all->philo_num].fork);
	all->philos[i - 1 % all->philo_num].bork = 0;
	printf("	%lims	%i has taken a fork\n", t, i + 1);
	printf("	%lims	%i has taken a fork\n", t, i + 1);
	printf("	%lims	%i is eatting\n", t, i + 1);
	//eatting = all->philos[i].time_to_eat + t;
	// if (*ded_time < get_time())
	// 	philo_ded(i, all);
	usleep(all->philos[i].time_to_sleep * 1000);
	all->philos[i].times_eatin--;
	pthread_mutex_unlock(&all->philos[i].fork);
	pthread_mutex_unlock(&all->philos[(i + 1) % all->philo_num].fork);
	all->philos[i].bork = 1;
	all->philos[i - 1 % all->philo_num].bork = 1;
	*ded_time = all->philos[i].time_to_die + get_time();
}

void	*phylo_run(t_philo *philos)
{
	int		i;
	t_all	*all;
	long	ded_time;

	all = philos->all;
	i = philos->id;
	usleep(1000);
	ded_time = philos->time_to_die + get_time();
	while (all->has_ded == 0 && philos->times_eatin != 0)
	{
		printf("	%lims	%i is thinking\n", get_time(), i + 1);
		while (all->has_ded == 0)
		{
			if (ded_time < get_time())
				philo_ded(i, all);
			if (all->philos[(i + 1) % all->philo_num].bork
				&& philos->bork && all->has_ded == 0 && all->philo_num > 1)
			{
				eat(all, i, &ded_time);
				break ;
			}
		}
		psleep(all, i);
	}
	return (NULL);
}

int	main(int argc, char	**argv)
{
	t_all	all;

	if (argc < 5)
		return (0);
	all.philo_num = ft_atoi(argv[1]);
	all.philos = malloc(sizeof(t_philo) * all.philo_num);
	all.has_ded = 0;
	spawn_philos(argv, &all, argc);
	//run_threads(&all);
	while (all.has_ded == 0 && check_eat(&all))
		;
	usleep(10000);
	return (1);
}
