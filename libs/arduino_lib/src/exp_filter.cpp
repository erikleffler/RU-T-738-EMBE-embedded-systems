#include "exp_filter.h"

ExpFilter::ExpFilter(float weight) : weight(weight) {}
ExpFilter::ExpFilter() : weight(0.5) {}

float ExpFilter::filter(float value) {
	float filtered = this->weight * value + (1 - this->weight) * this->previous;
	this->previous = filtered;
	return filtered;
}
