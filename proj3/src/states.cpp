#include "states.h"

constexpr int led_pin = LED_BUILTIN;
constexpr int knob_pin = A4;

// ###################
// ###### State ######


State::~State() {
}

void State::set_context(Context *context) {
	this->context_ = context;
}


// #####################
// ###### Context ######


Context::Context() {}

Context::Context(State *state) : state_(nullptr) {

	this->transition_to(state);
}

Context::~Context() {
	delete this->state_;
}

void Context::do_work() {
	this->state_->do_work();
}

void Context::transition_to(State *state) {

	if (this->state_ != nullptr){
		this->state_->on_exit();
		delete this->state_;
	}

	this->state_ = state;
	this->state_->set_context(this);
	this->state_->on_entry();

	Serial.println("Context: Transition");
	Serial.flush();
}

void Context::process_cmd(char command[]) {
	
	/*if(command == "reset") {
		state_->on_reset();
	}*/

}


// ############################
// ###### Initialization ######


void Initialization::on_entry() {

	Serial.begin(115200);
	Serial.setTimeout(-1);
  	while(!Serial);

	Serial.println("Initialization / entry");
	
	/*
	pinMode(led_pin, OUTPUT);
	pinMode(knob_pin, INPUT);
*/


}

void Initialization::do_work() {

	this->context_->transition_to(new PreOperational());
}

void Initialization::on_exit() {
	Serial.println("Initialization / exit");
}


// ############################
// ###### PreOperational ######


void PreOperational::on_entry() {

	Serial.println("PreOperational / entry");
	this->prev_millis = millis();

}

void PreOperational::do_work() {



/*
	delay(1000);
	uint64_t current_millis = millis();
	if(current_millis - this->prev_millis >= this->millis_to_wait) {

		this->prev_millis = current_millis;

		digitalWrite(led_pin, !digitalRead(led_pin)); // toggle
	}
	*/
}

void PreOperational::on_exit() {
	Serial.println("PreOperational / exit");
}

void PreOperational::on_reset() {

	Serial.println("PreOperational / reset");

	this->context_->transition_to(new Initialization());
}
