#include<tasks.h>

void*incrementTask(void*param){

	while(1){

		sleep(3);

		pthread_mutex_lock(&sharedVariableMutex);

		gSharedFifo.put(gSharedFifo.head() + 1);

		printf("IncrementTask: shared fifo head is %d\n", gSharedFifo.head());
		fflush(0);

		pthread_mutex_unlock(&sharedVariableMutex);

	}
}

