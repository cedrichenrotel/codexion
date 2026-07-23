/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 14:11:20 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/23 11:33:51 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>

/*allocation de memoire a ma liste de prioriter*/
int init_heap(t_hall *hall, t_heap *heap)
{
	heap->tab_id_coder = malloc(sizeof(t_element) * hall->number_of_coders);
	if (!heap->tab_id_coder)
		return(print_err("heap.c", "Allocation failed"));
	heap->capacity_max = hall->number_of_coders;
	heap->size_actually = 0;
	return (SUCCESS);
}
static void heapify_up(t_heap *heap)
{
	int	i;
	int	parent;
	t_element tmp;

	i = heap->size_actually -1;
	parent = (i - 1) / 2;
	
	while (heap->tab_id_coder[i].key < heap->tab_id_coder[parent].key
			&& i > 0)
		{
			tmp.key = heap->tab_id_coder[parent].key;
			tmp.id_coder = heap->tab_id_coder[parent].id_coder;
			heap->tab_id_coder[parent].key = heap->tab_id_coder[i].key;
			heap->tab_id_coder[parent].id_coder = heap->tab_id_coder[i].id_coder;
			heap->tab_id_coder[i].key = tmp.key;
			heap->tab_id_coder[i].id_coder = tmp.id_coder;
			i = parent;
			parent = (i - 1) / 2;
		}
}

/*remonte id_coder dans le tas selon sa cles*/
int	heap_push(t_heap *heap, int id_coder, long long key)
{

	if (heap->size_actually < heap->capacity_max)
	{
		heap->tab_id_coder[heap->size_actually].key = key;
		heap->tab_id_coder[heap->size_actually].id_coder = id_coder;
		heap->size_actually++;

		swap_element(heap);
		return (SUCCESS);
	}
	return (print_err("heap.c", "Current size > capacity_max"));
}
