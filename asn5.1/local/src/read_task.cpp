#include "read_task.h"

extern pthread_mutex_t char_fifo_mutex;
extern CharFifo char_fifo;

void *readTask(void *param) {
    char c;

    while (1) {
        c = getchar();

		pthread_mutex_lock(&char_fifo_mutex);
		pushToCharFifo(&char_fifo, c);
		pthread_mutex_lock(&char_fifo_mutex);
    }
}
