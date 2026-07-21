/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 11:09:21 by cehenrot          #+#    #+#             */
/*   Updated: 2026/07/21 19:04:45 by cehenrot         ###   ########.fr       */
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

typedef enum e_status
{
	ACQUIRING_DONGLES,
	COMPILING,
	DEBUGGING,
	REFACTORING,
	BURNOUT,
}					t_status;

typedef struct s_dongle
{
	int					accessible;
	int					index;
	long				last_release; // dernier relachement
	pthread_mutex_t		acces_dongle;
	pthread_cond_t		doorbell;

}					t_dongle;

typedef struct s_hall t_hall;

typedef struct s_coders
{
	int					id_coder;
	long				last_compile_start; // derniere compilation
	int					number_of_compiles;
	t_status			current_status;
	pthread_t			thread;
	pthread_mutex_t		acces_coder;
	t_dongle			*left_dongle;
	t_dongle			*right_dongle;
	t_hall				*hall;

}					t_coders;

typedef struct s_hall
{
	int					nb_pass;
	// protege le compteur partagercontre simultaner par plusieurs threads
	pthread_mutex_t		secu_nb_pass;
	// sert a reveiller un codeur qui attend un badge
	pthread_cond_t		doorbell_pass;
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

typedef struct s_element
{
	long	key;
	int		id_coder;
}			t_element;

typedef struct s_heap
{
	t_element	*tab_id_coder;
	int			capacity_max;
	int			size_actually;

}			t_heap;

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
int			init_hall(char **argv, t_hall *hall);
int			init_heap(t_hall *hall, t_heap *heap);
int			print_error_parse(char *msg, char *arg);

#endif
