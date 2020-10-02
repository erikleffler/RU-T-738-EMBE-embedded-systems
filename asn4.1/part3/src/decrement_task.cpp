#include<tasks.h>

void*decrementTask(void*param){

	while(1) {
		sleep(7);

		pthread_mutex_lock(&sharedVariableMutex);

		gSharedFifo.get();

		printf("DecrementTask: shared fifo head is %d\n", gSharedFifo.head());
		fflush(0);

		pthread_mutex_unlock(&sharedVariableMutex);

	}
}


