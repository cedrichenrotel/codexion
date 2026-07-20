/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 17:07:12 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/20 13:26:20 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_hall	hall;
	int	i;
	int	j;

	if (!parse_intput(argc, argv))
		return (-1);
	if (converted_and_stock_arg(argv, &hall))
	{
		if (!init_dongles(&hall))
			return (-1);
		if (!init_coders(&hall))
		{
			free_dongle(&hall, hall.number_of_coders);
			return (-1);
		}
		i = 0;
		while (i < hall.number_of_coders)
		{
			pthread_create(&hall.coders.hread[i], NULL, routine());
			i++;
		}
	}
	else
		return (-1);
	free_dongle(&hall, hall.number_of_coders);
	free_coder(&hall, hall.number_of_coders);
	return (0);
}
