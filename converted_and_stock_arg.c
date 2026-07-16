/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converted_and_stock_arg.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 17:55:16 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/16 10:10:23 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int converted_and_stock_arg(char **argv, t_hall *hall)
{
    hall -> number_of_coders = atoi(argv[1]);
    hall -> time_to_burnout = atoi(argv[2]);
    hall -> time_to_compile = atoi(argv[3]);
    hall -> time_to_debug = atoi(argv[4]);
    hall -> time_to_refactor = atoi(argv[5]);
    hall -> dongle_cooldown = atoi(argv[6]);
    hall -> number_of_compiles_required = atoi(argv[7]);
    
    if (strcmp("fifo", argv[8]) == 0)
        hall -> scheduler = FIFO;
    else
        hall -> scheduler = EDF;
    return (1);
}