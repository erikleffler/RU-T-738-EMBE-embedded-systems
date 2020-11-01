#include <operat.h>
#include <init.h>
#include <preoperat.h>
#include <stop.h>


void Operational_state::on_do()
{
    if(this->context_->mode == 2)   // ambient
    {
        input_ph = this->context_->photocell_ptr->read(); 
        filtered_input_ph = this->context_->filter_ptr->smooth(input_ph);
        this->context_->led_ptr->set_val(filtered_input_ph);
    }
    else if(this->context_->mode == 1) this->context_->led_ptr->set_hi();   // high
    else if(this->context_->mode == 0) this->context_->led_ptr->set_lo();   // low

    // check if error has occured
    input_ph = this->context_->photocell_ptr->read(); 
    filtered_input_ph = this->context_->filter_ptr->smooth(input_ph);

    // 0 = short circuit and 255 = open circuit
    if(filtered_input_ph == 0 || filtered_input_ph == 255) {
        this->context_->last_was_operational = true;
        this->context_->command_stop();
    }
}

void Operational_state::on_entry()
{
    Serial.println("Start operational state");
    Serial.println("In case of returning to initialization- or preoperation state, type 'r' or 'p'.");
}

void Operational_state::on_exit()
{
    Serial.println("End operational state");
}
  
void Operational_state::on_command_reset() 
{
    Serial.println("set state to initialization");
    this->context_->transition_to(new Initialization_state);
}

void Operational_state::on_command_preoperation()
{   
    Serial.println("set state to preoperation");
    this->context_->transition_to(new Preoperational_state);    
}

void Operational_state::on_command_stop()
{
    Serial.println("set state to stopped");
    this->context_->transition_to(new Stopped_state); 
}