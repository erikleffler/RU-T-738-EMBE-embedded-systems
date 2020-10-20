#include "fifo.h"

void inline circularIncrement(char** p, char* base, size_t size) {
	*p += 1;

	ptrdiff_t diff = *p - base;
	if(diff == size) {
		*p = base;
	}
}

int8_t initCharFifo(CharFifo *char_fifo, size_t size) {
    char_fifo->size = size;
    char_fifo->buffer = (char *)malloc(size);

    if (char_fifo->buffer == NULL) return -1;

    char_fifo->first = char_fifo->buffer;
    char_fifo->last = char_fifo->buffer;

    char_fifo->possibly_empty = 1;

    return 1;
}

void destroyCharFifo(CharFifo *char_fifo) { free(char_fifo->buffer); }

void pushToCharFifo(CharFifo *char_fifo, char c) {

    *char_fifo->last = c;

	circularIncrement(&char_fifo->last, char_fifo->buffer, char_fifo->size);


    // If overflow, overwrite and move first
    if (char_fifo->last == char_fifo->first) 
		circularIncrement(&char_fifo->first, char_fifo->buffer, char_fifo->size);

    // Can't be empty next time if we just pushed
    char_fifo->possibly_empty = 0;
}

uint8_t charFifoIsEmpty(CharFifo *char_fifo) {
    return char_fifo->first == char_fifo->last && char_fifo->possibly_empty;
}

char readFromCharFifo(CharFifo *char_fifo) {

    char c = *char_fifo->first;

    if (charFifoIsEmpty(char_fifo)) {
		circularIncrement(&char_fifo->last, char_fifo->buffer, char_fifo->size);
	}

	circularIncrement(&char_fifo->first, char_fifo->buffer, char_fifo->size);

	// Can be empty next time if we just read.
    char_fifo->possibly_empty = 1;

    return c;
}
