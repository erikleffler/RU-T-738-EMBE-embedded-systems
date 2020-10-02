#include <fifo.h>
#define inc_offset_mod(p, offset, mod) 

Fifo::Fifo() : start(buffer), end(buffer), last_was_get(true)
{

}

inline void Fifo::circular_increment(int **p)
{
	*p += 1;
	if(*p == (this->buffer + FIFO_SIZE)) {
		*p = this->buffer;
	}
}

int Fifo::get()
{
	int fi = *this->start;

	if(!this->is_empty()) {
		this->circular_increment(&this->start);
	} 
	this->last_was_get = true;
    return fi;
}

void Fifo::put(int item)
{
	if(this->is_full()) { // Overflow
		this->circular_increment(&this->start);
	}

	*(this->end) = item;

	this->circular_increment(&this->end);

	this->last_was_get = false;
}

const int Fifo::head() {
	return *this->start;
}

bool Fifo::is_empty()
{
    return this->start == this->end && this->last_was_get;
}

bool Fifo::is_full()
{
    return this->start == this->end && !this->last_was_get;
}

void Fifo::reset()
{
	this->start = buffer;
	this->end = buffer;
	this->last_was_get = true;
}
