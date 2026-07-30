/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aquering_dongles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 11:47:24 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/30 17:46:57 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <unistd.h>

/*compare et range dans 2 pointeur en ordre croissant*/
static	void	sort_dongles(t_coders *coder, t_dongle **first, t_dongle **second)
{
	if (coder->id_coder % 2)
	{
		*first = coder->right_dongle;
		*second = coder->left_dongle;
	}
	else
	{	
		*first = coder->left_dongle;
		*second = coder->right_dongle;
	}
}

/*valider les 3 conditions simultanner pour recuperer dongle
	-si id-coder n est pas en test de liste de prioriter
	-si le premier dongle est accessible
	-si le temp de repos n est pas respecter*/

static	int	dongle_not_ready(t_coders *coder, t_dongle *dongle)
{
	int			top_heap;
	int			accessible;
	int			id_coder;
	long long	in_cooldown;
	long long	cooldown;

	top_heap = dongle->tab_priority->tab_id_coder[0].id_coder;
	accessible = dongle->accessible;
	cooldown = coder->hall->dongle_cooldown;
	in_cooldown = get_time_ms() - dongle->last_release;
	id_coder = coder->id_coder;
	return (top_heap != id_coder || !accessible || in_cooldown < cooldown);
	
}

static	int	acquire_one_dongle(t_coders *coder, t_dongle *dongle,
									long long key)
{
	struct timespec cooldown_time;
 
	pthread_mutex_lock(&dongle->acces_dongle);
	heap_push(dongle->tab_priority, coder->id_coder, key);
	while (coder->hall->burnout != 1 && dongle_not_ready(coder, dongle))
	{
		cooldown_time.tv_sec = (get_time_ms() + 50) / 1000; //donne les secondes entières
		cooldown_time.tv_nsec = ((get_time_ms() + 50) % 1000) * 1000000; //donne le reste en nanosecondes
		pthread_cond_timedwait(&dongle->doorbell, &dongle->acces_dongle
			, &cooldown_time);
	}
	pthread_mutex_lock(&coder->hall->secu_burnout);
	if (coder->hall->burnout)
	{
		pthread_mutex_unlock(&coder->hall->secu_burnout);
		pthread_mutex_unlock(&dongle->acces_dongle);
		return (ERROR);
	}
	heap_pop(dongle->tab_priority);
	dongle->accessible = 0;
	pthread_mutex_unlock(&dongle->acces_dongle);
	pthread_mutex_unlock(&coder->hall->secu_burnout);
	return (SUCCESS);
}

int	aquiring_dongles(t_coders *coder)
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
	
	if (!acquire_one_dongle(coder, first, key))
		return (ERROR);
	print_log(coder, "has taken a dongle");
	if (!acquire_one_dongle(coder, second, key))
		return (ERROR);
	print_log(coder, "has taken a dongle");
	change_status(coder, COMPILING);
	return (SUCCESS);
}
