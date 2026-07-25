/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 14:11:20 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/24 16:51:45 by cehenrot         ###   ########.fr       */
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

/*le nouvel élément arrive en bas (dernière position), potentiellement
trop petit pour être là → on le compare à son parent et on remonte
(heapify_up)*/
int	heap_push(t_heap *heap, int id_coder, long long key)
{

	if (heap->size_actually < heap->capacity_max)
	{
		heap->tab_id_coder[heap->size_actually].key = key;
		heap->tab_id_coder[heap->size_actually].id_coder = id_coder;
		heap->size_actually++;

		heapify_up(heap);
		return (SUCCESS);
	}
	return (print_err("heap.c", "Current size > capacity_max"));
}
static	void	heapify_down(t_heap *heap)
{
	int	last_elem;

	last_elem = heap->size_actually -1;

	heap->tab_id_coder[0].key = heap->tab_id_coder[last_elem].key;
	heap->tab_id_coder[0].id_coder = heap->tab_id_coder[last_elem].id_coder;
	heap->size_actually --;
}
/*l'élément déplacé vient du bas du tas mais atterrit en haut (racine) → il est
potentiellement trop grand pour être là → il faut le comparer à ses enfants et
le faire descendre (heapify_down)*/
int	heap_pop(t_heap *heap)
{
	int	parent;
	int	kid_l;
	int	kid_r;
	int	size_act;
	t_element tmp;
	t_element *element;
	parent = 0;
	size_act = heap->size_actually;
	while ()
	{
		kid_l = (2 * parent) + 1;
		kid_r = (2 * parent) + 2;
		tmp.key = heap->tab_id_coder[parent].key;
		tmp.id_coder = heap->tab_id_coder[parent].id_coder;
		if (kid_l < size_act && heap->tab_id_coder[kid_l].key < heap->tab_id_coder[parent].key)
		{
			heap->tab_id_coder[parent].key = heap->tab_id_coder[kid_l].key;
			heap->tab_id_coder[parent].id_coder = heap->tab_id_coder[kid_l].id_coder;
		}
		if (kid_l < size_act && heap->tab_id_coder[kid_r].key < heap->tab_id_coder[parent].key)
		{
			heap->tab_id_coder[parent].key = heap->tab_id_coder[kid_r].key;
			heap->tab_id_coder[parent].id_coder = heap->tab_id_coder[kid_r].id_coder;
		}
		else if (heap->tab_id_coder[parent].key ==  heap->tab_id_coder[0].key)
			return;
	}
}
