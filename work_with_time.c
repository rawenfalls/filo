#include "philo.h"

// Возвращает время
unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
//контролирует usleep
void	usleep_control(int wait)
{
	unsigned long	time;

	time = get_time();
	while (get_time() < time + (unsigned long)wait)
		usleep(50);
	
}