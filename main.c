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
void    printf_time(void)
{
    struct timeval end;
    static struct timeval *start = NULL;

    if (start == NULL)
    {
        start = malloc(sizeof(end));
        gettimeofday(start, NULL);
    }
    gettimeofday(&end, NULL);
    printf("%ld\n", (end.tv_sec * 1000000 + end.tv_usec) -
    (start->tv_sec * 1000000 + start->tv_usec));
}

void	spawn_philos(char **argv, t_all *all)
{
	int	i;

	i = -1;
	while(++i < all->forks)
		all->philos[i].time_to_die = ft_itoa(argv[1]);
	i = -1;
	while(++i < all->forks)
		all->philos[i].time_to_die = ft_itoa(argv[2]);
	i = -1;
	while(++i < all->forks)
		all->philos[i].time_to_die = ft_itoa(argv[3]);
}

int main(int argc, char	**argv)
{
	t_all all;

	all.forks = argc - 1;
	all.philo_num = argc - 1;
	all.philos = malloc(sizeof(t_philo) * (argc - 1));
	spawn_philos(argv, &all);
    printf_time();
}