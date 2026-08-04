/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 17:23:04 by cehenrot          #+#    #+#             */
/*   Updated: 2026/08/03 14:20:17 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <unistd.h>

/*locks the mutex for this dongle, makes it accessible again at 1, logs the time
broadcasts (to wake up the coders) to see who’s at the top of the list, and 
unlocks the mutexx */
static	void	release_dongles(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->acces_dongle);
	dongle->accessible = 1;
	dongle->last_release = get_time_ms();
	pthread_cond_broadcast(&dongle->doorbell);
	pthread_mutex_unlock(&dongle->acces_dongle);
}

/*displays the message along with the time, calls the release_dongle function 
and changes the status to move on to the next stage*/
void	compiling(t_coders *coder)
{
	print_log(coder, "is compiling");
	pthread_mutex_lock(&coder->acces_coder);
	coder->last_compile_start = get_time_ms();
	pthread_mutex_unlock(&coder->acces_coder);
	usleep(coder->hall->time_to_compile * 1000);
	release_dongles(coder->right_dongle);
	release_dongles(coder->left_dongle);
	pthread_mutex_lock(&coder->acces_coder);
	coder->number_of_compiles += 1;
	pthread_mutex_unlock(&coder->acces_coder);
	change_status(coder, DEBUGGING);
}
