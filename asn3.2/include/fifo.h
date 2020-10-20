#ifndef FIFO_H
#define FIFO_H

const int FIFO_SIZE = 5;

class Fifo
{
public:
    Fifo();
    int get();
    void put(int item);
    bool is_empty();
    bool is_full();
    void reset();
private:
	inline void circular_increment(int **p);
	int *start;
	int *end;
	int bad_end; // For bad_fifo implementation
    int buffer[FIFO_SIZE];
	bool last_was_get; // Keep track if last call was to get or put.
					   // This helps to distinguish is_full() and is_empty().
};

#endif // FIFO_H
