#ifndef FIFO
#define FIFO

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct charFifo {
    size_t size;
    char *buffer;
    char *first;
    char *last;
    uint8_t possibly_empty;
} CharFifo;


int8_t initCharFifo(CharFifo *char_fifo, size_t size);
void destroyCharFifo(CharFifo *char_fifo);
void pushToCharFifo(CharFifo *char_fifo, char c);
uint8_t charFifoIsEmpty(CharFifo *char_fifo);
char readFromCharFifo(CharFifo *char_fifo);

#endif // FIFO
