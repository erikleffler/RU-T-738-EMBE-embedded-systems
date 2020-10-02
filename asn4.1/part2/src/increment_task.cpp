#include<tasks.h>

void*incrementTask(void*param){

	while(1){

		sleep(3);

		pthread_mutex_lock(&sharedVariableMutex);

		gSharedVariable++;

		printf("IncrementTask: shared var is %d\n", gSharedVariable);
		fflush(0);

		pthread_mutex_unlock(&sharedVariableMutex);

	}
}

