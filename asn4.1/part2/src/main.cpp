#include "tasks.h"

pthread_t incrementTaskObj;
pthread_t decrementTaskObj;

int gSharedVariable = 0;
pthread_mutex_t sharedVariableMutex;

int main(void) {
	
	pthread_mutex_init(&sharedVariableMutex, NULL);


	pthread_create(&incrementTaskObj,NULL,incrementTask,NULL);
	pthread_create(&decrementTaskObj,NULL,decrementTask,NULL);

	pthread_join(incrementTaskObj, NULL);
	pthread_join(decrementTaskObj, NULL);

	return 0;
}

