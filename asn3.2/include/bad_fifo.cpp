#include <fifo.h>

Fifo::Fifo() : start(0), end(0)
{

}

int Fifo::get()
{
	int fi = buffer[this->start];

	for(int i = this->start; i < this->end - 1; i++) {
		buffer[i] = buffer[i + 1];
	}
	this->end -= 1;

    return fi;
}

void Fifo::put(int item)
{
	if(this->end == FIFO_SIZE) {

		for(int i = 0; i < this->end - 1; i++) {
			buffer[i] = buffer[i + 1];
		}
		this->end -= 1;
	}

	buffer[this->end] = item;
	this->end += 1;
}

bool Fifo::is_empty()
{
    return this->end == 0;
}

bool Fifo::is_full()
{
    return this->end == FIFO_SIZE;
}

void Fifo::reset()
{

	this->end = 0;
	this->start = 0;
}
