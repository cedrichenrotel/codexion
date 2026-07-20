/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongle_and_coders.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 16:23:32 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/20 17:40:57 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*appel des fonctions qui permet initialiser les tableau de structure des
dongle et des coders. Libert la memoire si probleme d allocation*/
int	init_dongle_and_coders(t_hall *hall)
{
	if (!init_dongles(hall))
		return (ERROR);
	if (!init_coders(hall))
	{
		free_dongle(hall, hall->number_of_coders);
		return (ERROR);
	}
	return (SUCCESS);
}