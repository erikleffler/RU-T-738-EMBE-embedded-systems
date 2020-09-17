
void State::enter() {
	Serial.println("Entering state " + this->id);
}

void State::exit() {
	Serial.println("Exiting state " + this->id);
}


