/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 17:07:12 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/31 13:33:09 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_hall	hall;

	if (!parse_intput(argc, argv))
		return (ERROR);
	if (init_hall(argv, &hall))
	{
		if (!init_dongle_and_coders(&hall))
		{
			free_mutex_hall(&hall);
			return (ERROR);
		}
		if (!run_coders(&hall))
		{
			free_dongle(&hall, hall.number_of_coders);
			free_coder(&hall, hall.number_of_coders);
			free_mutex_hall(&hall);
			return (ERROR);
		}
	}
	else
		return (ERROR);
	free_dongle(&hall, hall.number_of_coders);
	free_coder(&hall, hall.number_of_coders);
	free_mutex_hall(&hall);
	return (SUCCESS);
}
