#include "philo.h"

//Сообщение об ошибке выводит ERROR который горит красным и мигает, а так же строку, возвращяет 1.
int	error_alert(char* str)
{
	printf("\33[5m\33[41mERROR\033[0m %s\n",str);
	return (1);
}
//Возвращает преобразованную строку в число, дополнительных проверок не делает
int	ft_atoi(char *str)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
		res = res * 10 + (*str++ - '0');
	return ((int)(res * sign));
}
//проверяет ввод на соответствие параметров, а так же заполняет структуру
int	parser(t_maind	*mdata, char **argv, int argc)
{
	if (argc != 5 && argc != 6)
		return (1);
	mdata->n_of_philo = ft_atoi(argv[1]);
	mdata->t_t_die = ft_atoi(argv[2]);
	mdata->t_t_eat = ft_atoi(argv[3]);
	mdata->t_t_sleep = ft_atoi(argv[4]);
	mdata->die = 0;
	mdata->t_must_eat = -1;
	if (argc == 6)
		mdata->t_must_eat = ft_atoi(argv[5]);
	return (0);
}
//инициализируем философов
void	init_philo(t_maind *mdata, int i)
{
	mdata->philo[i].id = i + 1;
	mdata->philo[i].r_fork = i;
	mdata->philo[i].maind = mdata;
	mdata->philo[i].how_phil_eat = 0;
	if (i == 0)
		mdata->philo[i].l_fork = mdata->n_of_philo - 1;
	else
		mdata->philo[i].l_fork = i - 1;
	mdata->philo[i].t_last_eat = get_time();
}
//выделяем память для философов и вилок, инициализируем мютексы,
// запускаем функцию для инициализации философов
int	init_fork_philo(t_maind *mdata)
{
	int	i;

	mdata->philo = malloc(sizeof(t_philo) * mdata->n_of_philo);
	if (!mdata->philo)
		return(error_alert("can't malloc memory on philo"));
	mdata->fork = malloc(sizeof(pthread_mutex_t) * mdata->n_of_philo);
	if (!mdata->fork)
	{
		free(mdata->philo);
		return (error_alert("can't malloc memory on fork"));
	}
	i = -1;
	while (++i < mdata->n_of_philo)
	{
		pthread_mutex_init(&mdata->fork[i], NULL);
		init_philo(mdata, i);
	}
	return (0);
}
//проверяем что ниодин из философов не умер, проверяем сколько раз
//должен поесть философ, после чего блокируем правую и левую вилку,
//о чем выводим сообщение, филосов ест, мы записываем последнее время еды,
//разблокируем вилки, после чего филосов идет спать и думать
void	live(t_philo *philo)
{
	while (!philo->maind->die 
		&& philo->how_phil_eat != philo->maind->t_must_eat)
	{
		pthread_mutex_lock(&philo->maind->fork[philo->r_fork]);
		pthread_mutex_lock(&philo->maind->fork[philo->l_fork]);
		printf("%lu %d has taken a fork\n", get_time() -
			philo->maind->start_time, philo->id);
		printf("%lu %d has taken a fork\n", get_time() -
			philo->maind->start_time, philo->id);
		printf("%lu %d is eating\n", get_time()-
			philo->maind->start_time, philo->id);
		usleep_control(philo->maind->t_t_eat);
		philo->t_last_eat = get_time();
		pthread_mutex_unlock(&philo->maind->fork[philo->r_fork]);
		pthread_mutex_unlock(&philo->maind->fork[philo->l_fork]);
		if (philo->how_phil_eat != philo->maind->t_must_eat)
		{
			printf("%lu %d is sleeping\n", get_time() -
				philo->maind->start_time, philo->id);
			usleep_control(philo->maind->t_t_sleep);
			printf("%lu %d is thinking\n", get_time() -
				philo->maind->start_time, philo->id);
		}	
		//philo->how_phil_eat++;
	}
}

int	check_death(t_maind *mdata)
{
	int				i;
	unsigned long	now_t;

	i = 0;
	while (1)
	{
		while (i < mdata->n_of_philo)
		{
			now_t = get_time();
			if (mdata->philo[i].how_phil_eat == mdata->n_of_philo)
				return (1);
			if (now_t - mdata->philo[i].t_last_eat > 
				(unsigned long)mdata->t_t_die)
			{
				mdata->die = 1;
				printf("\33[5m\33[41m%lu %d died\033[0m\n", now_t - mdata->start_time, i + 1);
				return (1);
			}
			i++;
		}
		i = 0;
		usleep(1000);
	}
	return (0);
}

void	thread_create(t_maind	*mdata)
{
	int	i;

	i = 0;
	while (i < mdata->n_of_philo)
	{
		pthread_create(&mdata->philo[i].thread, NULL,
			(void*)live, &mdata->philo[i]);
		usleep(100);
		i += 2;
	}
	i = 1;
	while (i < mdata->n_of_philo)
	{
		pthread_create(&mdata->philo[i].thread, NULL,
			(void*)live, &mdata->philo[i]);
		usleep(100);
		i += 2;
	}
	if (check_death(mdata))
		return ;
	i = -1;
	while (++i < mdata->n_of_philo)
		pthread_join(mdata->philo[i].thread, NULL);
}

int main(int argc, char *argv[])
{
	t_maind	mdata;
	int		i;

	if (parser(&mdata, argv, argc))
		return (error_alert(":wrong number of parameters"));
	if (init_fork_philo(&mdata))
		return (error_alert(":can't init fork"));
	mdata.start_time = get_time();
	thread_create(&mdata);
	free(mdata.fork);
	free(mdata.philo);
	i = -1;
	while(++i < mdata.n_of_philo)
		pthread_mutex_destroy(&mdata.fork[i]);
	return (0);
}
