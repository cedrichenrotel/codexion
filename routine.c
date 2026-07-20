/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 09:27:19 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/20 13:20:26 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>
#include <stdio.h>

void	*routine(void *arg)
{
	int val;
	val = *(int *)arg;
	printf("Bonjour, je suis un thread %d!\n", val);
	return (NULL);
}