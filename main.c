/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 17:07:12 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/17 16:47:04 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_hall	hall;

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
	}
	else
		return (-1);
	free_dongle(&hall, hall.number_of_coders);
	free_coder(&hall, hall.number_of_coders);
	return (0);
}
