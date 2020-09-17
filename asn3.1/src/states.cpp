#include "states.h"

Timer1 Yellow::timer = Timer1();

Context::Context() : current(new Red()), timeout(false) {

}

void Context::parseEvent(String event) {
	
	if(event.indexOf("stop") != -1) {
		this->current->stop(this);
	} else if (event.indexOf("timeout") != -1) {
		this->current->timeout(this);
	} else if (event.indexOf("go") != -1) {
		this->current->go(this);
	}

}

Red::Red() : id("red") {
	this->enter();
}

Red::~Red() {
	this->exit();
}

Yellow::Yellow() : id("yellow") {
	this->enter();
	this->timer.init(0.25);
}

Yellow::~Yellow() {
	this->timer.disable();
	this->exit();
}

Green::Green() : id("green") {
	this->enter();
}

Green::~Green() {
	this->exit();
}


void State::enter() {
	Serial.println("Entering state " + this->id);
}

void State::exit() {
	Serial.println("Exiting state " + this->id);
}

void Context::setCurrent(State *s){
	this->current = s;
}

void Red::go(Context* c) {
	c->setCurrent(new Green());
}

void Yellow::timeout(Context* c) {
	c->setCurrent(new Red());
}

void Green::stop(Context* c) {
	c->setCurrent(new Yellow());
}

