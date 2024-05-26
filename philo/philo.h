/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwick <cwick@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:18:20 by cwick             #+#    #+#             */
/*   Updated: 2024/05/26 16:36:43 by cwick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h> // write, usleep
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <stdbool.h>
# include <sys/time.h> // gettimeofday
# include <errno.h> // error numbers
# include <limits.h> // INT_MIN_MAX
# include <pthread.h> // mutex: init, destroy, lock, unlock
					// threads: create, join, detach

//	INPUT ERROR
# define INPUT_ERR_1 "ERROR: WRONG AMOUNT OF ARGUMENTS"
# define INPUT_ERR_2 "ERROR: INVALID INPUT CHARACTER"
# define MAX_INT_ERR "ERROR: NUMBER IS BIGGER THEN INT_MAX"
//	INIT ERROR
# define INIT_ERR_1 "ERROR: NOT ENOUGH PHILOSPHERS OR TIME VALUES ARE INCORRECT"
# define INIT_ERR_2 "ERROR WHILE PARSING INPUT"
# define MALLOC_ERR "ERROR WHILE ALLOCATING MEMORY"
//	ALLOC ERROR
# define ALLOC_ERR_1 "ERROR WHILE ALLOCATING THREADS IDs"
# define ALLOC_ERR_3 "ERROR WHILE ALLOCATING PHILOS"
# define ALLOC_ERR_2 "ERROR WHILE ALLOCATING FORKS"
//	THREAD ERROR
# define TH_ERR "ERROR WHILE CREATING THREADS"
# define JOIN_ERR "ERROR WHILE JOINING THREADS"
# define DET_ERR "ERROR WHILE DETACHING THREAD"
# define INIT_ERR_FORK "ERROR WHILE INIT FORKS"
# define MUTEX_ERR "ERROR WHILE CREATING MUTEX"
//	TIME ERROR
# define TIME_ERR "ERROR: UNABLE TO RETRIVE UTC"
//	PHILO MSG
# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

struct	s_philo;
struct	s_fork;

typedef struct s_fork
{
	long			fork_id;
	pthread_mutex_t	fork_mutex;
}	t_fork;

typedef struct s_data
{
	pthread_t		*tid;
	struct s_philo	*philos;
	long			philo_num;
	long			meals_nbr;
	long			dead;
	long			finished;
	long			death_time;
	long			eat_time;
	long			sleep_time;
	long			start_time;
	bool			end_simulation;
	t_fork			*fork;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	write;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_t		t1;
	t_fork			*first_fork;
	t_fork			*second_fork;
	long			id;
	long			meal_count;
	bool			full;
	long			status;
	long			eating;
	long			time_to_die;
	pthread_mutex_t	philo_mutex;
	pthread_mutex_t	*first_fork_mutex;
	pthread_mutex_t	*second_fork_mutex;
}	t_philo;

//	MAIN & UTILS
int		main(int argc, char **argv);
int		error_exit(char *error, t_data *table);
void	ft_exit(t_data *table);
void	clear_data(t_data *table);
int		ft_atoi(const char *str);
int		ft_usleep(__useconds_t time);
int		ft_strcmp(char *s1, char *s2);

//	CHECK INPUT
void	check_input(int argc, char **argv);
int		check_argc(int argc);
int		check_argv(int argc, char **argv);

//	THREADS
int		thread_init(t_data *table);
void	*routine(void *philo_ptr);
void	*supervisor(void *philo_ptr);
void	*monitor(void *data_ptr);

//	INIT DATA
int		init(t_data *table, int argc, char **argv);
int		data_init(t_data *table, int argc, char **argv);
int		fork_init(t_data *table);
void	philo_init(t_data *table);
int		alloc(t_data *table);
// void	assign_forks(t_data	*table, int philo_pos);

// SAFE FUNCTIONS
void	*safe_malloc(size_t bytes);

// // GETTERS & SETTERS
// void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
// bool	get_bool(pthread_mutex_t *mutex, bool *value);
// void	set_long(pthread_mutex_t *mutex, long *dest, long value);
// long	get_long(pthread_mutex_t *mutex, long *value);
// bool	simulation_finished(t_data *table);

// ACTIONS
void	messages(char *str, t_philo *philo);
long	get_time(void);
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
void	eat(t_philo * philo);
int		case_one(t_data *table);


#endif
