#include <Arduino.h>
#include "../../arduino_lib/include/timer_1.h"

class Context;
class State {

	public:

		virtual void go(Context* c) {};

		virtual void stop(Context* c) {};

		virtual void timeout(Context* c) {};

		void enter();

		void exit();

	private:

		String id;
};

class Context
{
	public:

		Context();

		void setCurrent(State *s);

		void parseEvent(String event);

		bool timeout;

	private:

		State *current;

};



class Red : public State {

	public:

		Red();
		~Red();

		virtual void go(Context* c);

	private:

		String id;
};

class Yellow : public State {

	public:

		Yellow();
		~Yellow();

		virtual void timeout(Context* c);

		static Timer1 timer;

	private:

		String id;
};

class Green : public State {

	public:

		Green();
		~Green();

		virtual void stop(Context* c);
	private:

		String id;
};
