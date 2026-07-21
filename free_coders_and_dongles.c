/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_coders_and_dongles.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 08:04:24 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/21 09:30:34 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	free_tab_coders_and_dongles(t_hall *hall)
{
	free_dongle(hall, hall->number_of_coders);
	free_coder(hall, hall->number_of_coders);
}