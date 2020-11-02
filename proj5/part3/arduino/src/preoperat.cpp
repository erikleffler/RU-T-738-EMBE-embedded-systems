#include <preoperat.h>
#include <init.h>
#include <operat.h>
#include <stop.h>

void Preoperational_state::on_do()
{
    /*
    // check if error occured
    input_ph = this->context_->photocell_ptr->read(); 
    filtered_input_ph = this->context_->filter_ptr->smooth(input_ph);

    // 0 = short circuit and 255 = open circuit
    if(filtered_input_ph == 0 || filtered_input_ph == 255) {
        this->context_->last_was_operational = false;
        this->context_->command_stop();
    }
    */
}

void Preoperational_state::on_entry()
{
    context_->state_num = 1;
    //Serial.println("Start Timer to toggle LED for 1Hz.");
    this->context_->timer_ptr->stop();
    this->context_->timer_ptr->start(1);
    //Serial.println("Configurate Operational Behavior by typing 'a', 'h' or 'l' for ambient, high or low mode.");
    //Serial.println("Change to Operational_State by typing 'o'.");
}

void Preoperational_state::on_exit()
{
    //Serial.println("Stop Timer and preoperational state");
    this->context_->timer_ptr->stop();
}
  
void Preoperational_state::on_command_reset() 
{
    //Serial.println("set state to initialization");
    this->context_->transition_to(new Initialization_state);
}

void Preoperational_state::on_command_config_ambient()
{
    //Serial.println("The operational behavior is now in the ambient mode");
    this->context_->mode = 2;
}

void Preoperational_state::on_command_config_high()
{
    //Serial.println("The operational behavior is now in the high mode");
    this->context_->mode = 1;
}

void Preoperational_state::on_command_config_low()
{
    //Serial.println("The operational behavior is now in the low mode");
    this->context_->mode = 0;
}

void Preoperational_state::on_command_operation()
{
    //Serial.println("set state to operation");
    this->context_->transition_to(new Operational_state);  
}

void Preoperational_state::on_command_stop()
{
    //Serial.println("set state to stopped");
    this->context_->transition_to(new Stopped_state); 
}