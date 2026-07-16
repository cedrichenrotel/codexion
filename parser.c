/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 14:35:13 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/15 17:21:27 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <string.h>

int validation_scheduler(char *scheduler)
{
	if (strcmp("fifo", scheduler) != 0 && strcmp("edf", scheduler) != 0)
		return (print_error("Invalid scheduler", scheduler));
	return (1);
}

int validation_numbers(char *numbers)
{
	int len_numbers;

	len_numbers = strlen(numbers);

	if (len_numbers > 10)
		return (print_error("The numeric value is too long to be converted to "
			"an integer", numbers));
		
	if (len_numbers == 10 && strcmp("2147483647", numbers) < 0)
		return (print_error("Value is too large to be converted to an integer",
			numbers));
	return (1);
}

int parse_arg(char *arg, int index, int argc)
{
	int	i;

	if (strlen(arg) == 0)
	{
		fprintf(stderr, "[ERROR] parser_input: Empty argumentn\n");
		return (0);
	}
	
	i = 0;
		while (arg[i])
		{
			if (index != argc - 1 && !ft_isdigit(arg[i]))
				return (print_error("Invalid arguments", arg));
			
			i++;
		}
		
		if (index != argc - 1 && !validation_numbers(arg))
			return (0);

		if (index == argc - 1 && !validation_scheduler(arg))
			return (0);
	return (1);
}

int	parse_intput(int argc, char **argv)
{
	int i;

	if (argc != 9)
	{
		fprintf(stderr,
				"[ERROR] parser_input: "
				"Invalid number of arguments -> %d/9\n", argc);
		return 0;
	}

	i = 1;
	while (i < argc)
	{
		if (!parse_arg(argv[i], i, argc))
			return (0);
		i++;
	}
	return (1);
}
