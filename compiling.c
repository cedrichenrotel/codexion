/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 17:23:04 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/27 18:49:13 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <unistd.h>

void	compiling(t_coders *coder)
{
	print_log(coder, "is compiling");
	coder->last_compile_start = get_time_ms();

	usleep(coder->hall->time_to_compile * 1000);
}