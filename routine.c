/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 09:27:19 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/24 11:48:45 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*Fonction exécutée par chaque thread coder — c'est son
cycle de vie complet. Elle doit faire tourner le coder en boucle à travers
les états ACQUIRING_DONGLES → COMPILING → ..., en gérant l'acquisition sans
deadlock de ses deux dongles voisins, jusqu'à ce qu'il ait atteint
number_of_compiles_required (ou qu'il "meure" de burnout faute d'avoir
compilé à temps)*/
void	*routine(void *arg)
{
	t_coders *coder = (t_coders *)arg;
	// t_hall	*hall = coder->hall;
	
	while (coder->number_of_compiles < coder->hall->number_of_compiles_required)
	{
		if (coder->current_status == ACQUIRING_DONGLES)
			aquiring_dongles(coder);
		// else if (coder->current_status == COMPILING)
		// 	compiling(coder);
		// else if (coder->current_status == DEBUGGING)
		// 	debugging(coder);
		// else if (coder->current_status == REFACTORING)
		// 	refactoring(coder);
		// else
		// {
		// 	//check_burnout(&coder);
		// 	break;
		// }
			
		coder->number_of_compiles ++;
	}
	return (arg);
}
