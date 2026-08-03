/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 17:07:12 by cehenrot          #+#    #+#             */
/*   Updated: 2026/08/03 15:48:02 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_hall	hall;

	if (!parse_intput(argc, argv))
		return (ERROR);
	if (init_hall(argv, &hall))
	{
		if (!init_dongle_and_coders(&hall))
		{
			free_mutex_hall(&hall);
			return (ERROR);
		}
		if (!run_coders(&hall))
		{
			free_dongle(&hall, hall.number_of_coders);
			free_coder(&hall, hall.number_of_coders);
			free_mutex_hall(&hall);
			return (ERROR);
		}
	}
	else
		return (ERROR);
	free_dongle(&hall, hall.number_of_coders);
	free_coder(&hall, hall.number_of_coders);
	free_mutex_hall(&hall);
	return (SUCCESS);
}
/* Mineur — cas limites, peu probables mais réels

5. init_hall.c → init_hall_locks() : nettoyage d'erreur incohérent
Si pthread_mutex_init(&hall->secu_burnout, ...) échoue, le code fait pthread_mutex_destroy(&hall->secu_burnout) juste après — détruire un mutex qui vient d'échouer à s'initialiser est indéfini. En plus, ce chemin ne nettoie pas les trois mutex/cond déjà initialisés avant lui (secu_nb_pass, doorbell_pass, secu_log) — fuite sur cette branche. pthread_mutex_init échoue quasiment jamais en pratique (uniquement en cas de mémoire épuisée), donc impact très faible, mais présent.

6. Lectures de hall->burnout sans verrou à plusieurs endroits
execution_condition() dans routine.c, la condition du while dans acquire_one_dongle(), et la boucle principale de monitor_burnout() lisent toutes hall->burnout sans prendre secu_burnout. C'est une vraie data race au sens strict du standard C, sans conséquence observée sur x86 dans mes tests, mais techniquement non garanti.

⚪ Cosmétique / dette

7. Fichiers objets orphelins dans le dossier : aquering_dongles.o et free_coders_and_dongles.o ne correspondent à aucun .c actuel (probablement des restes d'un renommage de fichier). Ils ne sont pas utilisés par le Makefile donc sans danger, mais à nettoyer (make fclean + vérifier qu'ils ne réapparaissent pas).*/