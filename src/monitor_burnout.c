/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_burnout.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 13:12:30 by cehenrot          #+#    #+#             */
/*   Updated: 2026/08/04 14:36:11 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <unistd.h>

int	burnout(t_hall *hall)
{
	int	burnout;

	pthread_mutex_lock(&hall->secu_burnout);
	burnout = hall->burnout;
	pthread_mutex_unlock(&hall->secu_burnout);
	return (burnout);
}

static	void	*check_burnout(t_hall *hall, int *current_total)
{
	int			i;
	long long	time_elapsed;

	i = 0;
	while (i < hall->number_of_coders)
	{
		pthread_mutex_lock(&hall->coders[i].acces_coder);
		time_elapsed = get_time_ms() - hall->coders[i].last_compile_start;
		if (time_elapsed >= hall->time_to_burnout)
		{
			pthread_mutex_unlock(&hall->coders[i].acces_coder);
			change_status(&hall->coders[i], BURNOUT);
			print_log(&hall->coders[i], "burned out");
			pthread_mutex_lock(&hall->secu_burnout);
			hall->burnout = 1;
			pthread_mutex_unlock(&hall->secu_burnout);
			return (NULL);
		}
		*(current_total) += hall->coders[i].number_of_compiles;
		pthread_mutex_unlock(&hall->coders[i].acces_coder);
		i++;
	}
	return (NULL);
}

void	*monitor_burnout(void *arg)
{
	t_hall	*hall;
	int		total_compiles_required;
	int		current_total;

	hall = (t_hall *)arg;
	total_compiles_required = hall->number_of_coders
		* hall->number_of_compiles_required;
	current_total = 0;
	while (current_total < total_compiles_required)
	{
		current_total = 0;
		if (current_total == total_compiles_required)
			break ;
		check_burnout(hall, &current_total);
		if (hall->burnout == 1)
			break ;
		if (current_total >= total_compiles_required)
			break ;
		usleep(500);
	}
	return (NULL);
}
