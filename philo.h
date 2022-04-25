#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <errno.h>
# include <sys/time.h>
# include <limits.h>

# define ERROR		1
# define CORRECT	0

typedef struct s_philo
{
	int				id;
	int				how_phil_eat;
	int				r_fork;
	int				l_fork;
	pthread_t		thread;
	unsigned long	t_last_eat;
	struct s_maind	*maind;
}	t_philo;

typedef struct s_maind
{
	t_philo		*philo;
	pthread_mutex_t	*fork;
	unsigned long	start_time;
	int				n_of_philo;
	int				t_t_die;
	int				t_t_eat;
	int				t_t_sleep;
	int				t_must_eat;
	int				die;
}	t_maind;

unsigned long	get_time(void);
void			usleep_control(int wait);


#endif