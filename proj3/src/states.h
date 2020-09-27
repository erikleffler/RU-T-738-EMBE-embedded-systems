#include <Arduino.h>

class Context;

class State {

	public:

		virtual ~State();

		void set_context(Context *context_);

		virtual void do_work() = 0;

		virtual void on_entry() = 0;
		virtual void on_exit() = 0;
		virtual void on_reset() = 0;

	protected:

		Context *context_;
};

class Context {

	public:

		Context();

		Context(State *state);

		~Context();

		void do_work();

		void transition_to(State *state);

		void process_cmd(char command[]);

		State *state_;

	private:


};

class Initialization : public State {


	public:

		void do_work() override;

		void on_entry() override;

		void on_exit() override;

		void on_reset() override {};

};

class PreOperational : public State {


	public:

		void do_work() override;

		void on_entry() override;

		void on_exit() override;

		void on_reset() override;

	private:

		uint64_t prev_millis;

		static constexpr uint64_t millis_to_wait = 1000;

		

};





