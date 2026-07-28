/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 09:27:19 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/28 19:07:06 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void	simulate_phase(t_coders *coder, char *msg, t_status status
						, long long time)
{
	print_log(coder, msg);
	usleep(time * 1000);
	change_status(coder, status);
}

/*Fonction exécutée par chaque thread coder — c'est son
cycle de vie complet. Elle doit faire tourner le coder en boucle à travers
les états ACQUIRING_DONGLES → COMPILING → ..., en gérant l'acquisition sans
deadlock de ses deux dongles voisins, jusqu'à ce qu'il ait atteint
number_of_compiles_required (ou qu'il "meure" de burnout faute d'avoir
compilé à temps)*/
void	*routine(void *arg)
{
	t_coders *coder = (t_coders *)arg;
	int	burnout;
	int	nb_compil;
	int nb_compil_req;
	
	burnout = coder->hall->burnout;
	nb_compil = coder->number_of_compiles;
	nb_compil_req = coder->hall->number_of_compiles_required;
	while (burnout == 0 && nb_compil < nb_compil_req)
	{
		if (coder->current_status == ACQUIRING_DONGLES)
			aquiring_dongles(coder);
		else if (coder->current_status == COMPILING)
			compiling(coder);
		else if (coder->current_status == DEBUGGING)
			simulate_phase(coder, "is debugging", REFACTORING,
							coder->hall->time_to_debug);
		else if (coder->current_status == REFACTORING)
			simulate_phase(coder, "is refactoring", ACQUIRING_DONGLES,
							coder->hall->time_to_refactor);
	}
	return (arg);
}
