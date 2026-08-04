/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 17:16:13 by cehenrot          #+#    #+#             */
/*   Updated: 2026/08/04 09:30:01 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <unistd.h>

/*Convert `gettimeofday` (seconds + milliseconds) to a single value in 
milliseconds*/
long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/*A function that calculates the time elapsed from the start of execution to
the start time of a state (acquiring_dongle, compiling, etc.)*/
long long	timer(t_coders *coder)
{
	long long	time_start;

	time_start = coder->hall->start_time;
	return (get_time_ms() - time_start);
}

void	print_log(t_coders *coder, char *msg)
{
	if (!burnout(coder->hall))
		log_line(coder, msg);
}

void	log_line(t_coders *coder, char *msg)
{
	pthread_mutex_lock(&coder->hall->secu_log);
	printf("%lld %d %s\n", timer(coder), coder->id_coder, msg);
	pthread_mutex_unlock(&coder->hall->secu_log);
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
