/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 17:16:13 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/16 10:12:19 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
int print_error(char *msg, char *arg)
{
	fprintf(stderr, "[ERROR] parser_input: %s -> '%s'\n", msg, arg);
	return (0);
}