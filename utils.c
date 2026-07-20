/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 17:16:13 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/17 10:54:12 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <unistd.h>

int print_error_parse(char *msg, char *arg)
{
	fprintf(stderr, "[ERROR] parser.c: %s -> '%s'\n", msg, arg);
	return (0);
}
int print_err(char *msg1, char *msg2)
{
	fprintf(stderr, "[ERROR] %s: %s\n", msg1, msg2);
	return (0);
}

void print_struct(t_hall *hall)
{
	printf("nombre de codeur: %d\n", hall -> number_of_coders);
	printf("temp de burnout: %ld\n", hall -> time_to_burnout);
	printf("temp de compil.: %ld\n", hall -> time_to_compile);
	printf("temp de debug: %ld\n", hall -> time_to_debug);
	printf("temp de refacto.: %ld\n", hall -> time_to_refactor);
	printf("temp de recharge: %ld\n", hall -> dongle_cooldown);
	printf("temp de compil. recom: %d\n", hall -> number_of_compiles_required);
	printf("planificateur: %d\n", hall -> scheduler);
}