/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_coders.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 17:05:49 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/21 13:13:36 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static	int	start_hall_coders(t_hall *hall)
{
	/*Fonction pthread_create : c'est le cycle de
	vie d'un coder, exécuté en parallèle pour chacun.*/
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
		if(pthread_join(hall->coders[i].thread, NULL) != 0)
			return (print_err("run_coders.c", "Failed to join thread"));
		i++;
	}
	return (SUCCESS);
}

int	run_coders(t_hall *hall)
{
	if (!start_hall_coders(hall))
		return (ERROR);
	if (!join_hall_coders(hall))
		return (ERROR);
	return (SUCCESS);
}