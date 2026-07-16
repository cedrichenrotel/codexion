/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 17:07:12 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/16 10:09:07 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
    t_hall hall;
    
    if (!parse_intput(argc, argv))
        return (-1);
        
    if (converted_and_stock_arg(argv, &hall))
    {
        printf("trololo\n");
        
    }
    else
    {
        fprintf(stderr, "Initialization of struct hall failed\n");
        return (-1);
    }
    return (0);   
}
