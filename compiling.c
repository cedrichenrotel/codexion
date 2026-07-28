/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 17:23:04 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/28 10:43:49 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <unistd.h>

/*verouille le mutex de ce dongle, remet accessible a 1, enregistre l'heure
broacast(reveil les coders) pour voir qui est en tete de liste et deverouille
le mutex */
static	void	release_dongles(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->acces_dongle);
	dongle->accessible = 1;
	dongle->last_release = get_time_ms();
	pthread_cond_broadcast(&dongle->doorbell);
	pthread_mutex_unlock(&dongle->acces_dongle);
}
/*affiche le message avec le temp, appel la fonction release_dongle et change 
	le status pour passer a l'etaoe suivante*/
void	compiling(t_coders *coder)
{
	print_log(coder, "is compiling");
	
	pthread_mutex_lock(&coder->acces_coder);
	coder->last_compile_start = get_time_ms();
	pthread_mutex_unlock(&coder->acces_coder);

	usleep(coder->hall->time_to_compile * 1000);
	release_dongles(coder->left_dongle);
	release_dongles(coder->right_dongle);

	pthread_mutex_lock(&coder->acces_coder);
	coder->number_of_compiles += 1;
	pthread_mutex_unlock(&coder->acces_coder);

	change_status(coder, DEBUGGING);
}
