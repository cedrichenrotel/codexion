/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 09:27:19 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/23 13:48:01 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static	void	aquiring_dongles(t_coders *coder)
{
	t_dongle	*first;
	t_dongle	*second;
	long long	key;
	long long	deadline;
	struct timespec cooldown_time;

	/*compare et range dans 2 pointeur en ordre croissant*/
	if (coder->left_dongle->index < coder->right_dongle->index)
	{
		first = coder->left_dongle;
		second = coder->right_dongle;
	}
	else
	{	
		first = coder->right_dongle;
		second = coder->left_dongle;
	}
	/*bloc le premier dongle*/
	pthread_mutex_lock(&first->acces_dongle);
	deadline = coder->last_compile_start + coder->hall->time_to_burnout;
	if (coder->hall->scheduler == EDF)
		key = deadline;
	else
		key = get_time_ms();
	
	/*mettre dongle comme prioriter*/
	heap_push(first->tab_priority, coder->id_coder, key);
	
	/*valider les 3 conditions simultanner pour recuperer dongle
		-si id-coder n est pas en test de liste de prioriter
		-si le premier dongle est accessible
		-si le temp de repos n est pas respecter*/
	while (first->tab_priority->tab_id_coder[0].id_coder != coder->id_coder
		|| !first->accessible
		|| get_time_ms() - first->last_release < coder->hall->dongle_cooldown)
	{
		cooldown_time.tv_sec = (get_time_ms() + 50) / 1000; //donne les secondes entières
		cooldown_time.tv_nsec = ((get_time_ms() + 50) % 1000) * 1000000; //donne le reste en nanosecondes
		pthread_cond_timedwait(&first->doorbell, &first->acces_dongle
			, &cooldown_time); /*permet: 1. mettre le coder en pause
										 2. libert temporairement le mutex
										 3. réveille automatiquement après un court délai pour re-tester la condition*/
	}

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
