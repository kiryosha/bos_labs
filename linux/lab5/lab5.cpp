#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctime>
#include <errno.h>
#include <fcntl.h>

using namespace std;

bool signalled = false;
pthread_mutex_t mutex;
pthread_cond_t cv;

void* threadFunction(void* i)
{
	while(1)
	{
		srand(time(0));
		sleep(1);
		int id = (intptr_t)i;
		if(signalled)
		{
			cout << "\nПоток " << id << " завершил работу!";
			pthread_exit(0);
		}
		pthread_mutex_lock(&mutex);
		cout << "Thread " << id << endl;
		pthread_mutex_unlock(&mutex);
		sleep(1 + rand() % 10);
	}
	return NULL;
}

int main(int argc, char* argv[])
{
	int coutThread = 0;
	coutThread = atoi(argv[1]);
	pthread_t threads[coutThread];
	if(argc == 2 && argv[1] == string("/?"))
	{
		cout << "Сreator: Ikonnikov Kirill Mikhailovich\nGroup student 'BI-31'\nAvailable options: /? <cout thread>\n";
		return 0;
	}
	else if(coutThread == 0)
	{
		cout << "Example: ./lab5 <cout thread>\n";
		return 0;
	}
	int fd;
	fd = open("error", O_CREAT|O_EXCL);
	if ( fd < 0 ) 
	{
		cout << "The file is already running!" << endl;
		return 0;
	}
	else
	{
		pthread_mutex_init(&mutex, NULL);
		for (int i = 1; i <= coutThread; i++)
			pthread_create(&threads[i], NULL, threadFunction, (void *)(intptr_t)i);
		while (true)
		{
			if (getchar() == EOF)
			{
				signalled = true;
				system("rm -f error");
				sleep(20);
				break;
			}
		}
		pthread_mutex_destroy(&mutex);
		cout << endl;
	}
	return 0;
}
