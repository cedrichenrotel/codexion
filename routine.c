/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 09:27:19 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/21 11:26:12 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void	*routine(void *arg)
{
	/*Fonction exécutée par chaque thread coder — c'est son
	cycle de vie complet. Elle doit faire tourner le coder en boucle à travers
	les états ACQUIRING_DONGLES → COMPILING → ..., en gérant l'acquisition sans
	deadlock de ses deux dongles voisins, jusqu'à ce qu'il ait atteint
	number_of_compiles_required (ou qu'il "meure" de burnout faute d'avoir
	compilé à temps)*/

	t_coders *coder = (t_coders *)arg;
	
	while (coder->number_of_compiles < coder->hall->number_of_compiles_required)
	{
		coder->number_of_compiles ++;
	}

}