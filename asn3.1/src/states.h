#include <Arduino.h>

class State {

	public:

		virtual void go() {};

		virtual void stop() {};

		virtual void timeout() {};

		void enter();

		void exit();

	private:

		static String id;
}

class Red : public State {
		virtual void go();
}

class Yellow : public State {
		virtual void timeout();
}

class Green : public State {
		virtual void stop();
}
