#include <Arduino.h>

class ISRCbNode {

	public:

		ISRCbNode(
			void (*cb)(),
			float freq,
			bool repeating,
			ISRCbNode* next, // Use pointers since we allow nullptr
			ISRCbNode* prev  // for head and tail of list.
		);

		void Unlink();

	private:

		void (*cb)();

		const float freq;

		const bool repeating;

		ISRCbNode* next;
		ISRCbNode* prev;

};

class Timer {

	public:
		//
		// Delete copy constructor, singleton class
		TimerManager(const TimerManager&) = delete;
		TimerManager& operator= (const TimerManager&) = delete;

		virtual void init();

		void CallCmpACallbacks();
		void CallCmpBCallbacks();

	protected:
		Timer(uint16_t max_compare);

	private:

		const uint16_t max_compare;

		uint16_t prescaler;

		ISRCbNode* cmp_a_callbacks;
		ISRCbNode* cmp_b_callbacks;

};

class Timer0 : Timer {

	public:
		void init();
};

class Timer1 : Timer {

	public:
		void init();
};

class Timer2 : Timer {

	public:
		void init();
};

// Singleton class to manage timer interrupts
class TimerManager {

	public:

		// Delete copy constructor, singleton class
		TimerManager(const TimerManager&) = delete;
		TimerManager& operator=(const TimerManager&) = delete;

		// Get the single instance
		static TimerManager& GetInstance();

		void Timer0CompareA();
		void Timer0CompareB();
		void Timer1CompareA();
		void Timer1CompareB();
		void Timer2CompareA();
		void Timer2CompareB();

	private:

		// Hide constructor
		TimerManager();

		Timer0 timer0;
		Timer1 timer1;
		Timer2 timer2;

		static TimerManager singleton_instance;

};
