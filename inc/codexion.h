/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehenrot <cehenrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 11:09:21 by cehenrot          #+#    #+#             */
/*   Updated: 2026/08/04 08:34:50 by cehenrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <sys/time.h>

# define SUCCESS	1
# define ERROR	0

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

typedef struct s_hall	t_hall;
typedef struct s_heap	t_heap;

typedef struct s_dongle
{
	int					accessible;
	int					index;
	long long			last_release;
	pthread_mutex_t		acces_dongle;
	pthread_cond_t		doorbell;
	t_heap				*tab_priority;

}					t_dongle;

typedef struct s_coders
{
	int					id_coder;
	long long			last_compile_start;
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
	pthread_mutex_t				secu_log;
	pthread_mutex_t				secu_nb_pass;
	pthread_mutex_t				secu_burnout;
	pthread_cond_t				doorbell_pass;
	pthread_t					monitor_thread;
	t_dongle					*dongles;
	t_coders					*coders;
	t_scheduler					scheduler;
	int							nb_pass;
	int							number_of_coders;
	int							number_of_compiles_required;
	int							burnout;
	long long					time_to_burnout;
	long long					time_to_compile;
	long long					time_to_debug;
	long long					time_to_refactor;
	long long					dongle_cooldown;
	long long					start_time;

}					t_hall;

typedef struct s_element
{
	long long	key;
	int			id_coder;

}			t_element;

typedef struct s_heap
{
	t_element	*tab_id_coder;
	int			capacity_max;
	int			nb_actually;

}			t_heap;

void		*routine(void *arg);
void		compiling(t_coders *coder);
void		*monitor_burnout(void *arg);
void		free_mutex_hall(t_hall *hall);
void		free_coder(t_hall *hall, int index);
void		log_line(t_coders *coder, char *msg);
void		free_dongle(t_hall *hall, int index);
void		heap_swap(t_heap *heap, int a, int b);
void		print_log(t_coders *coder, char *msg);
void		change_status(t_coders *coder, t_status status);

int			burnout(t_hall *hall);
int			heap_pop(t_heap *heap);
int			run_coders(t_hall *hall);
int			init_coders(t_hall *hall);
int			init_dongles(t_hall *hall);
int			aquiring_dongles(t_coders *coder);
int			print_err(char *msg1, char *msg2);
int			parse_intput(int argc, char **argv);
int			init_dongle_and_coders(t_hall *hall);
int			init_hall(char **argv, t_hall *hall);
int			init_heap(t_hall *hall, t_heap *heap);
int			print_error_parse(char *msg, char *arg);
int			heap_push(t_heap *heap, int id_coder, long long key);

long long	get_time_ms(void);
long long	timer(t_coders *coder);

#endif
