/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 14:11:20 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/27 15:49:01 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>

/*allocation de memoire a ma liste de prioriter*/
int	init_heap(t_hall *hall, t_heap *heap)
{
	heap->tab_id_coder = malloc(sizeof(t_element) * hall->number_of_coders);
	if (!heap->tab_id_coder)
		return (print_err("heap.c", "Allocation failed"));
	heap->capacity_max = hall->number_of_coders;
	heap->size_actually = 0;
	return (SUCCESS);
}

static	void	heapify_up(t_heap *heap)
{
	int	i;
	int	parent;

	i = heap->size_actually -1;
	parent = (i - 1) / 2;
	while (heap->tab_id_coder[i].key < heap->tab_id_coder[parent].key
		&& i > 0)
	{
		heap_swap(heap, parent, i);
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
/*l'élément déplacé vient du bas du tas mais atterrit en haut (racine) → il est
potentiellement trop grand pour être là → il faut le comparer à ses enfants et
le faire descendre (heapify_down)*/
static	int	heapify_down(t_heap *heap, int *i)
{
	int	kid_r;
	int	kid_l;
	int smallest;

	kid_l = (2 * *(i)) + 1;
	kid_r = (2 * *(i)) + 2;
	if (kid_l >= heap->size_actually)
		return (ERROR);
	else if (kid_r >= heap->size_actually)
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
/*premiere patrie du code permet de stocker et returner l'element de l'index 0, 
puis remonter le dernier element en tete de liste pour recaluler l'arbre
binaire */
int	heap_pop(t_heap *heap)
{
	int			last_elem;
	int			i;

	if (!heap->size_actually)
		return (print_err("heap.c", "No elements in tab_id_coder"));
	last_elem = heap->size_actually -1;
	heap->tab_id_coder[0].key = heap->tab_id_coder[last_elem].key;
	heap->tab_id_coder[0].id_coder = heap->tab_id_coder[last_elem].id_coder;
	heap->size_actually --;

	i = 0;
	while (i < heap->size_actually)
	{
		if (!heapify_down(heap, &i))
			break ;
	}
	return (SUCCESS);
}

