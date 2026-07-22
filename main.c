/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 17:07:12 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/22 09:03:30 by cehenrot         ###   ########.fr       */
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
			return (ERROR);
		if (!run_coders(&hall))
		{
			free_tab_coders_and_dongles(&hall);
			return (ERROR);
		}
		
	}
	else
		return (ERROR);
	free_tab_coders_and_dongles(&hall);
	return (SUCCESS);
}
