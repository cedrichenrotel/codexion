/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 11:09:21 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/16 10:05:26 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>

typedef enum e_scheduler
{
	FIFO,
	EDF,
}					t_scheduler;

typedef enum e_etat
{
	ACQUIRING_DONGLES,
	COMPILING,
	DEBUGGING,
	REFACTORING,
}					t_etat;

typedef struct s_dongle
{
	int				accessible;
	long last_release; // dernier relachement
	pthread_mutex_t	acces_dongle;
	pthread_cond_t	sonnets;

}					t_dongle;

typedef struct s_codeur
{
	pthread_t		thread;
	int				id_codeur;
	long last_compile_start; // derniere compilation
	int				number_of_compiles;
	t_etat			current_status;
	pthread_mutex_t	acces;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;

}					t_codeur;

typedef struct s_hall
{
	int nb_pass; // nombre de passe pour codeur (3/4)
	pthread_mutex_t	secu_nb_pass;
	pthread_cond_t sonnette_pass;
		// sert a reveiller un codeurqui attend un badge
	t_dongle		*dongles;
	t_codeur		*codeurs;
	pthread_mutex_t	secu_log;
	int				number_of_coders;
	long			time_to_burnout;
	long			time_to_compile;
	long			time_to_debug;
	long			time_to_refactor;
	long			dongle_cooldown;
	int				number_of_compiles_required;
	t_scheduler		scheduler;

}					t_hall;

int			ft_isdigit(int c);
int			print_error(char *msg, char *arg);
int			parse_intput(int argc, char **argv);
int			converted_and_stock_arg(char **argv, t_hall *hall);

#endif
