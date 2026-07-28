/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 17:16:13 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/28 11:44:15 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <unistd.h>

/*convertis gettimeofday (seconde+miliseconde) en une seul val en miliseconde*/
long long	get_time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	heap_swap(t_heap *heap, int a, int b)
{
	t_element	tmp;
	
	tmp.key = heap->tab_id_coder[a].key;
	tmp.id_coder = heap->tab_id_coder[a].id_coder;
	heap->tab_id_coder[a].key = heap->tab_id_coder[b].key;
	heap->tab_id_coder[a].id_coder = heap->tab_id_coder[b].id_coder;
	heap->tab_id_coder[b].key = tmp.key;
	heap->tab_id_coder[b].id_coder = tmp.id_coder;
}

void	print_log(t_coders *coder, char *msg)
{
	pthread_mutex_lock(&coder->hall->secu_log);
	printf("%lld %d %s\n", get_time_ms(), coder->id_coder, msg);
	pthread_mutex_unlock(&coder->hall->secu_log);
}
void	change_status(t_coders *coder, t_status status)
{
	pthread_mutex_lock(&coder->acces_coder);
	coder->current_status = status;
	pthread_mutex_unlock(&coder->acces_coder);
}
