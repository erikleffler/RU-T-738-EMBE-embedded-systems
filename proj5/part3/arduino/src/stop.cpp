#include <stop.h>
#include <preoperat.h>
#include <init.h>
#include <operat.h>




void Stopped_state::on_do()
{
    // check if error is still there
    input_ph = this->context_->photocell_ptr->read(); 
    filtered_input_ph = this->context_->filter_ptr->smooth(input_ph);

    if(!(filtered_input_ph == 0 || filtered_input_ph == 255)) {
        if(context_->last_was_operational == true) {
            Serial.println("set state to operation");
            this->context_->transition_to(new Operational_state); 
        }
        else {
            Serial.println("set state to preoperation");
            this->context_->transition_to(new Preoperational_state); 
        }
    }
}

void Stopped_state::on_entry()
{
    Serial.println("Start Timer to toggle LED for 2Hz.");
    this->context_->timer_ptr->stop();
    this->context_->timer_ptr->start(2);
    Serial.println("+++ Error: Open or short circuit +++");
    Serial.println("Change to previous State after solving the issue.");
}

void Stopped_state::on_exit()
{
    Serial.println("Stop Timer");
    this->context_->timer_ptr->stop();
}