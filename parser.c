/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 14:35:13 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/21 09:27:35 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static	int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static	int	validation_scheduler(char *scheduler)
{
	if (strcmp("fifo", scheduler) != 0 && strcmp("edf", scheduler) != 0)
		return (print_error_parse("Invalid scheduler", scheduler));
	return (SUCCESS);
}

static	int	validation_numbers(char *numbers)
{
	int	len_numbers;

	len_numbers = strlen(numbers);
	if (len_numbers > 10)
		return (print_error_parse("The numeric value is too long to be "
				"converted to an integer", numbers));
	if (len_numbers == 10 && strcmp("2147483647", numbers) < 0)
		return (print_error_parse("Value is too large to be converted to an "
				"integer", numbers));
	return (SUCCESS);
}

int	parse_arg(char *arg, int index, int argc)
{
	int	i;

	if (strlen(arg) == 0)
		return (print_err("parser.c", "Empty argument\n"));
	i = 0;
	while (arg[i])
	{
		if (index != argc - 1 && !ft_isdigit(arg[i]))
			return (print_error_parse("The argument is not a number", arg));
		i++;
	}
	if (index == 1 && atoi(arg) < 2)
		return (print_error_parse("Insufficient number of encoders", arg));
	if ((index != argc - 1 && !validation_numbers(arg)) ||
		(index == argc - 1 && !validation_scheduler(arg)))
		return (ERROR);
	return (SUCCESS);
}

int	parse_intput(int argc, char **argv)
{
	int	i;

	if (argc != 9)
	{
		fprintf(stderr,
			"[ERROR] parser.py: "
			"Invalid number of arguments -> %d/9\n", argc);
		return (ERROR);
	}
	i = 1;
	while (i < argc)
	{
		if (!parse_arg(argv[i], i, argc))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
