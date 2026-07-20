/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 12:20:26 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/20 08:59:09 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>
#include <stdio.h>

void	free_dongle(t_hall *hall, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		pthread_mutex_destroy(&hall->dongles[i].acces_dongle);
		pthread_cond_destroy(&hall->dongles[i].sonnets);
		i++;
	}
	free(hall->dongles);
	hall->dongles = NULL;
}

static	int	init(t_dongle *dongle)
{
	dongle->accessible = 1;
	dongle->last_release = 0;
	if (pthread_mutex_init(&dongle->acces_dongle, NULL) != 0
		|| pthread_cond_init(&dongle->sonnets, NULL) != 0)
		return (print_err("dongles.c", "Failed init dongle"));
	return (1);
}

int	init_dongles(t_hall *hall)
{
	int	nb_dongle;
	int	i;

	nb_dongle = hall->number_of_coders;
	hall->dongles = malloc(sizeof(t_dongle) * nb_dongle);
	if (!hall->dongles)
		return (print_err("dongles.c", "Allocation failed"));
	i = 0;
	while (i < nb_dongle)
	{
		if (!init(&hall->dongles[i]))
		{
			free_dongle(hall, i);
			return (0);
		}
		i++;
	}
	return (1);
}
