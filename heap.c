/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 14:11:20 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/31 14:45:31 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>

/*memory allocation for my priority list*/
int	init_heap(t_hall *hall, t_heap *heap)
{
	heap->tab_id_coder = malloc(sizeof(t_element) * hall->number_of_coders);
	if (!heap->tab_id_coder)
		return (print_err("heap.c", "Allocation failed"));
	heap->capacity_max = hall->number_of_coders;
	heap->nb_actually = 0;
	return (SUCCESS);
}

static	void	heapify_up(t_heap *heap)
{
	int	i;
	int	parent;

	i = heap->nb_actually -1;
	parent = (i - 1) / 2;
	while (heap->tab_id_coder[i].key < heap->tab_id_coder[parent].key
		&& i > 0)
	{
		heap_swap(heap, parent, i);
		i = parent;
		parent = (i - 1) / 2;
	}
}

/*the new element arrives at the bottom (last position), and may
be too small to be there → we compare it with its parent and move it up
(heapify_up)*/
int	heap_push(t_heap *heap, int id_coder, long long key)
{
	if (heap->nb_actually < heap->capacity_max)
	{
		heap->tab_id_coder[heap->nb_actually].key = key;
		heap->tab_id_coder[heap->nb_actually].id_coder = id_coder;
		heap->nb_actually++;
		heapify_up(heap);
		return (SUCCESS);
	}
	return (print_err("heap.c", "Current size > capacity_max"));
}

/*the element being moved comes from the bottom of the heap but ends up at the
top (root) → it is potentially too large to be there → it must be compared with 
its children and moved down (heapify_down)*/
static	int	heapify_down(t_heap *heap, int *i)
{
	int	kid_r;
	int	kid_l;
	int	smallest;

	kid_l = (2 * *(i)) + 1;
	kid_r = (2 * *(i)) + 2;
	if (kid_l >= heap->nb_actually)
		return (ERROR);
	else if (kid_r >= heap->nb_actually)
		smallest = kid_l;
	else
	{
		if (heap->tab_id_coder[kid_l].key <= heap->tab_id_coder[kid_r].key)
			smallest = kid_l;
		if (heap->tab_id_coder[kid_l].key > heap->tab_id_coder[kid_r].key)
			smallest = kid_r;
	}
	if (heap->tab_id_coder[smallest].key > heap->tab_id_coder[*(i)].key)
		return (ERROR);
	else
	{
		heap_swap(heap, smallest, *(i));
		*(i) = smallest;
	}
	return (SUCCESS);
}

/*The first part of the code stores and returns the element at index 0,
then moves the last element to the front of the list to recalculate the
binary tree */
int	heap_pop(t_heap *heap)
{
	int			last_elem;
	int			i;

	if (!heap->nb_actually)
		return (print_err("heap.c", "No elements in tab_id_coder"));
	last_elem = heap->nb_actually -1;
	heap->tab_id_coder[0].key = heap->tab_id_coder[last_elem].key;
	heap->tab_id_coder[0].id_coder = heap->tab_id_coder[last_elem].id_coder;
	heap->nb_actually --;
	i = 0;
	while (i < heap->nb_actually)
	{
		if (!heapify_down(heap, &i))
			break ;
	}
	return (SUCCESS);
}
