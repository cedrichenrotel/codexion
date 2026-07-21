/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongle_and_coders.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 16:23:32 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/21 18:34:12 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*appel des fonctions qui permet initialiser les tableau de structure des
dongle et des coders. Libert la memoire si probleme d allocation*/
int	init_dongle_and_coders(t_hall *hall)
{
	if (!init_hall_locks(hall))
        return (ERROR);
	if (!init_dongles(hall))
		return (ERROR);
	if (!init_coders(hall))
	{
		free_dongle(hall, hall->number_of_coders);
		return (ERROR);
	}
	return (SUCCESS);
}
