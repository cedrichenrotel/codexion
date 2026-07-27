/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 10:24:38 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/27 10:25:10 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

int	print_error_parse(char *msg, char *arg)
{
	fprintf(stderr, "[ERROR] parser.c: %s -> '%s'\n", msg, arg);
	return (ERROR);
}

int	print_err(char *msg1, char *msg2)
{
	fprintf(stderr, "[ERROR] %s: %s\n", msg1, msg2);
	return (ERROR);
}