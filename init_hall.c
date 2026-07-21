/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:55:16 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/21 19:03:26 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static	int	converted_and_stock_arg(char **argv, t_hall *hall)
{
	if (hall)
	{
		hall -> number_of_coders = atoi(argv[1]);
		hall -> time_to_burnout = atoi(argv[2]);
		hall -> time_to_compile = atoi(argv[3]);
		hall -> time_to_debug = atoi(argv[4]);
		hall -> time_to_refactor = atoi(argv[5]);
		hall -> number_of_compiles_required = atoi(argv[6]);
		hall -> dongle_cooldown = atoi(argv[7]);
		if (strcmp("fifo", argv[8]) == 0)
			hall -> scheduler = FIFO;
		else
			hall -> scheduler = EDF;
		return (SUCCESS);
	}
	else
	{
		fprintf(stderr, "Initialization of struct hall failed\n");
		return (ERROR);
	}
}

/*initialisation de tous les mutex de hall*/
static int	init_hall_locks(t_hall *hall)
{
	if (pthread_mutex_init(&hall->secu_nb_pass, NULL) != 0)
		return (print_err("init_hall.c", "Failed init secu_nb_pass"));
	if (pthread_cond_init(&hall->doorbell_pass, NULL) != 0)
	{
		pthread_mutex_destroy(&hall->secu_nb_pass);
		return (print_err("init_hall.c", "Failed init doorbell_pass"));
	}
	if (pthread_mutex_init(&hall->secu_log, NULL) != 0)
	{
		pthread_mutex_destroy(&hall->secu_nb_pass);
		pthread_cond_destroy(&hall->doorbell_pass);
		return (print_err("init_hall.c", "Failed init secu_log"));
	}
	return (SUCCESS);
}

int	init_hall(char **argv, t_hall *hall)
{
	if (!converted_and_stock_arg(argv, hall) || !init_hall_locks(hall))
		return (ERROR);
	return (SUCCESS);
}