/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 09:42:48 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/20 17:39:35 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>
#include <stdio.h>

void	free_coder(t_hall *hall, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		pthread_mutex_destroy(&hall->coders[i].acces_coder);
		i++;
	}
	free(hall->coders);
	hall->coders = NULL;
}

static	int	init(t_coders *coders, t_hall *hall, int index)
{
	int	nb_coders;
	int	index_left_dongle;

	nb_coders = hall->number_of_coders;
	coders->id_coder = index + 1;
	coders->last_compile_start = 0;
	coders->number_of_compiles = 0;
	coders->current_status = ACQUIRING_DONGLES;
	if (pthread_mutex_init(&coders->acces_coder, NULL) != 0)
		return (print_err("dongles.c", "Failed init coder"));
	coders->right_dongle = &hall->dongles[index];
	index_left_dongle = (index - 1 + nb_coders) % nb_coders;
	coders->left_dongle = &hall->dongles[index_left_dongle];
	return (SUCCESS);
}
/*allocation et initialisation d'un tableau t_coders[] */
int	init_coders(t_hall *hall)
{
	int	nb_coders;
	int	i;

	nb_coders = hall->number_of_coders;
	hall->coders = malloc(sizeof(t_coders) * nb_coders);
	if (!hall->coders)
		return (print_err("coders.c", "Allocation failed"));
	i = 0;
	while (i < nb_coders)
	{
		if (!init(&hall->coders[i], hall, i))
		{
			free_coder(hall, i);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}
