/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 09:27:19 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/31 14:10:31 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <unistd.h>

void	simulate_phase(t_coders *coder, char *msg, t_status status,
			long long time)
	{
	print_log(coder, msg);
	usleep(time * 1000);
	change_status(coder, status);
}

/*condition that causes the loop in routine() to stop*/
static	int	execution_condition(t_coders *coder)
{
	return (coder->hall->burnout == 0 && coder->number_of_compiles
		< coder->hall->number_of_compiles_required);
}

/*Function executed by each coder thread — this is its
entire lifecycle. It must cause the coder to loop through
the states ACQUIRING_DONGLES → COMPILING → ..., managing the acquisition of 
its two neighbouring dongles without deadlock, until it has reached
number_of_compiles_required (or ‘dies’ of burnout for failing to
compile in time)*/
void	*routine(void *arg)
{
	t_coders	*coder;

	coder = (t_coders *)arg;
	while (execution_condition(coder))
	{
		if (coder->current_status == ACQUIRING_DONGLES)
			aquiring_dongles(coder);
		else if (coder->current_status == COMPILING)
			compiling(coder);
		else if (coder->current_status == DEBUGGING)
			simulate_phase(coder, "is debugging", REFACTORING,
				coder->hall->time_to_debug);
		else if (coder->current_status == REFACTORING)
			simulate_phase(coder, "is refactoring", ACQUIRING_DONGLES,
				coder->hall->time_to_refactor);
	}
	return (arg);
}
