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
		printf("%ld\n", (end.tv_sec * 100 + end.tv_usec)
			- (start->tv_sec * 100 + start->tv_usec));
	}
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

int	assignnum(void)
{
	static int	i = -1;

	return (++i);
}

void	*phylo_run(void *vargp)
{
	int		i;
	t_all	*all;
	long	wake_up;
	long	eatting;
	long	ded_time;

	all = vargp;
	i = assignnum();
	ded_time = all->philos[i].time_to_die + get_time();
	while (all->has_ded == 0)
	{
		printf("	%lims	%i is thinking\n", get_time(), i);
		while (all->has_ded == 0)
		{
			printf("forks = %i\n", all->forks);
			printf("%li < %li\n", ded_time, get_time());
			if (ded_time < get_time())
				philo_ded(i, all);
			if (all->forks >= 2 && all->has_ded == 0)
			{
				all->forks -= 2;
				printf("	%lims	%i is eatting\n", get_time(), i);
				eatting = all->philos[i].time_to_eat + get_time();
				while (eatting >= get_time())
					get_time();
				ded_time = all->philos[i].time_to_die + get_time();
				printf("%li < %li\n", ded_time, get_time());
				all->forks += 2;
				break ;
			}
		}
		printf("	%lims	%i is sleeping\n", get_time(), i);
		wake_up = all->philos[i].time_to_sleep + get_time();
		while (wake_up >= get_time() && all->has_ded == 0)
			get_time();
	}
	return (NULL);
}



int	main(int argc, char	**argv)
{
	t_all	all;

	if (argc == 1)
		return (0);
	all.forks = 2;//ft_atoi(argv[1]);
	all.philo_num = ft_atoi(argv[1]);
	all.philos = malloc(sizeof(t_philo) * all.philo_num);
	all.has_ded = 0;
	spawn_philos(argv, &all);
	run_threads(&all);
}
