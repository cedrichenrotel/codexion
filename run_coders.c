/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_coders.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 17:05:49 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/31 13:46:19 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*The pthread_create function: this is a programmer’s life cycle,
executed in parallel for each one.*/
static	int	start_hall_coders(t_hall *hall)
{
	int	i;

	i = 0;
	while (i < hall->number_of_coders)
	{
		if (pthread_create(&hall->coders[i].thread, NULL, routine,
				&hall->coders[i]))
			return (print_err("run_coders.c", "Failed launch of the coders"));
		i++;
	}
	return (SUCCESS);
}

static	int	join_hall_coders(t_hall *hall)
{
	int	i;

	i = 0;
	while (i < hall->number_of_coders)
	{
		if (pthread_join(hall->coders[i].thread, NULL) != 0)
			return (print_err("run_coders.c", "Failed to join thread"));
		i++;
	}
	return (SUCCESS);
}

int	run_coders(t_hall *hall)
{
	if (!start_hall_coders(hall))
		return (ERROR);
	pthread_create(&hall->monitor_thread, NULL, monitor_burnout, hall);
	if (!join_hall_coders(hall))
		return (ERROR);
	pthread_join(hall->monitor_thread, NULL);
	return (SUCCESS);
}
