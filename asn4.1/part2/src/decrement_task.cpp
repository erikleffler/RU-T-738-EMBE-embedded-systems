#include<tasks.h>

void*decrementTask(void*param){

	while(1) {
		sleep(7);

		pthread_mutex_lock(&sharedVariableMutex);

		gSharedVariable--;

		printf("DecrementTask: shared var is %d\n",gSharedVariable);
		fflush(0);

		pthread_mutex_unlock(&sharedVariableMutex);

	}
}


