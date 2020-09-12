#pragma once
#include "analog_in.h"

class ExpFilter {

	public:

		ExpFilter(float weight);
		ExpFilter();

		float filter(float val);

	private:
		float previous;
		float weight;

};
