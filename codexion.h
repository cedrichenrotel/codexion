/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 11:09:21 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/21 11:14:51 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>

#define	SUCCESS	1
#define	ERROR	0

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
	BURNOUT,
}					t_etat;

typedef struct s_dongle
{
	int					accessible;
	long				last_release; // dernier relachement
	pthread_mutex_t		acces_dongle;
	pthread_cond_t		sonnets;

}					t_dongle;

typedef struct s_coders
{
	int					id_coder;
	long				last_compile_start; // derniere compilation
	int					number_of_compiles;
	t_etat				current_status;
	pthread_t			thread;
	pthread_mutex_t		acces_coder;
	t_dongle			*left_dongle;
	t_dongle			*right_dongle;
	t_hall				*hall;

}					t_coders;

typedef struct s_hall
{
	int					nb_pass; // nombre de passe pour codeur (3/4)
	pthread_mutex_t		secu_nb_pass;
	pthread_cond_t		sonnette_pass;
		// sert a reveiller un codeurqui attend un badge
	t_dongle			*dongles;
	t_coders			*coders;
	pthread_mutex_t		secu_log;
	int					number_of_coders;
	long				time_to_burnout;
	long				time_to_compile;
	long				time_to_debug;
	long				time_to_refactor;
	int					number_of_compiles_required;
	long				dongle_cooldown;
	t_scheduler			scheduler;

}					t_hall;

void		*routine(void *arg);
void		print_struct(t_hall *hall);
void		free_dongle(t_hall *hall, int index);
void		free_coder(t_hall *hall, int index);
void		free_tab_coders_and_dongles(t_hall *hall);

int			run_coders(t_hall *hall);
int			init_coders(t_hall *hall);
int			init_dongles(t_hall *hall);
int			print_err(char *msg1, char *msg2);
int			parse_intput(int argc, char **argv);
int			init_dongle_and_coders(t_hall *hall);
int			print_error_parse(char *msg, char *arg);
int			converted_and_stock_arg(char **argv, t_hall *hall);

#endif
