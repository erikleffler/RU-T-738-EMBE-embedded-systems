#include <fifo.h>

Fifo::Fifo()
{
	this->bad_end = 0;
}

int Fifo::get()
{
	int fi = buffer[0];

	for(int i = 0; i < this->bad_end - 1; i++) {
		buffer[i] = buffer[i + 1];
	}
	this->bad_end -= 1;

    return fi;
}

void Fifo::put(int item)
{
	if(this->bad_end == FIFO_SIZE) {

		for(int i = 0; i < this->bad_end - 1; i++) {
			buffer[i] = buffer[i + 1];
		}
		this->bad_end -= 1;
	}

	buffer[this->bad_end] = item;
	this->bad_end += 1;
}

bool Fifo::is_empty()
{
    return this->bad_end == 0;
}

bool Fifo::is_full()
{
    return this->bad_end == FIFO_SIZE;
}

void Fifo::reset()
{
	this->bad_end = 0;
}
