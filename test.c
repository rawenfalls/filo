// int main()
// {
// 	printf("\33[5m\33[41m\33[34mread\033[0mnorm\n");
// 	return (0);
// }

// void* routime(void* arg)
// {
// 	int index = *(int*)arg;
// 	printf("Test %d\n", index);
// 	free(arg);
// }

// void* routime()
// {
// 	printf("Test\n");
// 	sleep(3);
// 	printf("Ending tread\n");
// }
// int main()
// {
// 	pthread_t t1, t2;
// 	if (pthread_create(&t1, NULL, &routime, NULL) != 0)
// 	{
// 		return (1);
// 	}
// 	pthread_create(&t2, NULL, &routime, NULL);
// 	if (pthread_join(t1, NULL) != 0)
// 		return (2);
// 	pthread_join(t2, NULL);
// 	return 0;
// }

// int prime[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
// int main(int argc, char const *argv[])
// {
// 	pthread_t th[10];
// 	int i;
// 	for (i = 0; i < 10; i++)
// 	{
// 		int *a = malloc(sizeof(int));
// 		*a = i;
// 		if (pthread_create(&th[i], NULL, &routime, a) != 0)
// 			perror("Failed to create thread");
// 	}
// 	for (i = 0; i < 10; i++)
// 	{
// 		if (pthread_join(th[i], NULL) != 0)
// 			perror("Failed to join thread");
// 	}
// 	return 0;
// }

// pthread_mutex_t = mutex;

// void* roll_dice()
// {
// 	int value = (rand() % 6) + 1;
// 	int* result = malloc(sizeof(int));
// 	*result = value;
// 	//printf("%d\n", value);
// 	return (void*) result;
// }

// int main(int argc, char const *argv[])
// {
// 	int* res;
// 	srand(time(NULL));
// 	pthread_t th1;
// 	if (pthread_create(&th1, NULL, &roll_dice, NULL) != 0)
// 		return (1);
// 	if (pthread_join(th1, (void**) &res) != 0)
// 		return (2);
// 	printf("%p\n", res);
// 	printf("%d\n", *res);
// 	free(res);
// 	return 0;
// }

int mails = 0;
pthread_mutex_t mutex;

void* routine()
{
		pthread_mutex_lock(&mutex);
	for (int i = 0; i< 1000000; i++)
	{
		mails++;
	}
		pthread_mutex_unlock(&mutex);
}

int main(int argc, char const *argv[])
{
	pthread_t th[4];
	int i;
	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < 4; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)// or th + i
		{
			perror("Failed to create thread");
			return (i + 1);
		}
		printf("Thread %d has started\n", i);
	}
	for (i = 0; i < 4; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("Failed to join thread");
			return (i + 1 + 4);
		}
		printf("Thread %d has finished\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return 0;
}

// int prime[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

// void* routine(void* arg)
// {
// 	int index = *(int*)arg;
// 	int sum = 0;
// 	for (int i = 0; i < 5; i++)
// 		sum += prime[index + i];
// 	*(int*)arg = sum;
// 	printf("Half summ: %d\n", sum);
// 	return arg;
// }

// int main(int argc, char const *argv[])
// {
// 	pthread_t th[2];
// 	int i;
// 	for (i = 0; i < 2; i++)
// 	{
// 		int *a = malloc(sizeof(int));
// 		*a = i * 5;
// 		if (pthread_create(&th[i], NULL, &routine, a) != 0)
// 			perror("Failed to create thread");
// 	}
// 	int globalSumm = 0;
// 	for (i = 0; i < 2; i++)
// 	{
// 		int* r;
// 		if (pthread_join(th[i],(void**) &r) != 0)
// 			perror("Failed to join thread");
// 		globalSumm += *r;
// 		free(r);
// 	}
// 	printf("Global sum: %d\n", globalSumm);
// 	return 0;
// }
