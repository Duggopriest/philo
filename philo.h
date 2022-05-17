/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 17:22:26 by marvin            #+#    #+#             */
/*   Updated: 2022/05/15 17:22:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philo
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_eatin;
}	t_philo;

typedef struct s_all
{
	pthread_t	*thread_id;
	int			philo_num;
	int			forks;
	t_philo		*philos;
	int			has_ded;
}	t_all;

long	get_time(void);
void	printf_time(void);
int		ft_atoi(const char *str);

void	*phylo_run(void *vargp);
int		assignnum(void);
void	psleep(t_all *all, int i);

void	philo_ded(int i, t_all *all);
void	run_threads(t_all *all);
void	spawn_philos(char **argv, t_all *all, int argc);

#endif