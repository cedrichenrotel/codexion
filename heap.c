/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 14:11:20 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/22 16:44:49 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>

int init_heap(t_hall *hall, t_heap *heap)
{
	/*allocation de memoire a ma liste de prioriter*/
	heap->tab_id_coder = malloc(sizeof(t_element) * hall->number_of_coders);
	if (!heap->tab_id_coder)
		return(print_err("heap.c", "Allocation failed"));
	heap->capacity_max = hall->number_of_coders;
	heap->size_actually = 0;
	return (SUCCESS);
}
int	heap_push(t_heap *heap, int id_coder, long long key)
{
	int	i;

	if (heap->size_actually < heap->capacity_max)
	{
		i = 0;
		while (i < heap->capacity_max)
		{
			heap->tab_id_coder[i].key = key;
			heap->tab_id_coder[i].id_coder = id_coder;
			i++;
		}
		return (SUCCESS);
	}
	return (print_err("heap.c", "Current size > capacity_max"));
}
