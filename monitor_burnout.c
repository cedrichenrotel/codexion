/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_burnout.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 13:12:30 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/28 16:03:31 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <unistd.h>

void	*monitor_burnout(void *arg)
{
	t_hall *hall = (t_hall *)arg;
	int	cible;
	int	i;
	int	current_total;
	long long	time_elapsed;
	
	/*nombre de coder * nombre de compilation*/
	cible = hall->number_of_coders * hall->number_of_compiles_required;
	current_total = 0;
	
	while (current_total < cible)
	{
		if (current_total == cible)
			break;
		i = 0;
		while(i < hall->number_of_coders)
		{
			pthread_mutex_lock(&hall->coders[i].acces_coder);
			/*temp actuel - heure derniere compilation*/
			time_elapsed = get_time_ms() - hall->coders[i].last_compile_start;
			if (time_elapsed >= hall->time_to_burnout)
			{
				pthread_mutex_unlock(&hall->coders[i].acces_coder);
				change_status(&hall->coders[i], BURNOUT);
				print_log(&hall->coders[i], "burned out");
				pthread_mutex_lock(&hall->secu_burnout);
				hall->burnout = 1;
				pthread_mutex_unlock(&hall->secu_burnout);
				return (NULL);
			}
				
			/*somme de chaque nombre de compilation max que chaque coder
			peux faire*/
			current_total += hall->coders[i].number_of_compiles;
			pthread_mutex_unlock(&hall->coders[i].acces_coder);
			i++;
		}
		if (current_total >= cible)
			break;
		usleep(5000);
	}
	return (NULL);
}
