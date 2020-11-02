#include <init.h>
#include <preoperat.h>

void Initialization_state::on_entry()
{
  //Serial.println("Start initialization");
  context_->state_num = 0;
}

void Initialization_state::on_exit()
{
  //Serial.println("End intialization");
}

void Initialization_state::on_do()
{
	//Serial.println("Device starts up and initialize internal parameters");
    
  // LED setup
  this->context_->led_ptr->init();

  // Photocell setup
  this->context_->photocell_ptr->init();

  // Filter setup
  this->context_->filter_ptr->init();

  // Autonomously go to preoperational state 
	//Serial.println("Set state to preoperational");
	this->context_->transition_to(new Preoperational_state);
}