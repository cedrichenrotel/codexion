/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aquering_dongles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 11:47:24 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/28 11:59:00 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <unistd.h>

/*compare et range dans 2 pointeur en ordre croissant*/
static	void	sort_dongles(t_coders *coder, t_dongle **first, t_dongle **second)
{
	if (coder->left_dongle->index < coder->right_dongle->index)
	{
		*first = coder->left_dongle;
		*second = coder->right_dongle;
	}
	else
	{	
		*first = coder->right_dongle;
		*second = coder->left_dongle;
	}
}

/*valider les 3 conditions simultanner pour recuperer dongle
	-si id-coder n est pas en test de liste de prioriter
	-si le premier dongle est accessible
	-si le temp de repos n est pas respecter*/
static	void	acquire_one_dongle(t_coders *coder, t_dongle *dongle, long long key)
{
	struct timespec cooldown_time;

	pthread_mutex_lock(&dongle->acces_dongle);
	
	/*mettre coder comme prioriter*/
	heap_push(dongle->tab_priority, coder->id_coder, key);
	while (dongle->tab_priority->tab_id_coder[0].id_coder != coder->id_coder
		|| !dongle->accessible
		|| get_time_ms() - dongle->last_release < coder->hall->dongle_cooldown)
	{
		cooldown_time.tv_sec = (get_time_ms() + 50) / 1000; //donne les secondes entières
		cooldown_time.tv_nsec = ((get_time_ms() + 50) % 1000) * 1000000; //donne le reste en nanosecondes
		pthread_cond_timedwait(&dongle->doorbell, &dongle->acces_dongle
			, &cooldown_time); /*permet: 1. mettre le coder en pause
										 2. libert temporairement le mutex
										 3. réveille automatiquement après un court délai pour re-tester la condition*/
	}
	heap_pop(dongle->tab_priority);
	dongle->accessible = 0;
	pthread_mutex_unlock(&dongle->acces_dongle);
}

void	aquiring_dongles(t_coders *coder)
{
	t_dongle	*first;
	t_dongle	*second;
	long long	key;
	long long	deadline;

	sort_dongles(coder, &first, &second);

	deadline = coder->last_compile_start + coder->hall->time_to_burnout;
	if (coder->hall->scheduler == EDF)
		key = deadline;
	else
		key = get_time_ms();
	
	acquire_one_dongle(coder, first, key);
	print_log(coder, "has taken a dongle");
	acquire_one_dongle(coder, second, key);
	print_log(coder, "has taken a dongle");
	change_status(coder, COMPILING);
}
