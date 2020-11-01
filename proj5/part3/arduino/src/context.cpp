#include <context.h>
/**
 * The Context defines the interface of interest to clients. It also maintains a
 * reference to an instance of a State subclass, which represents the current
 * state of the Context.
 */

Context::Context(State *state) : state_(nullptr)
{
    this->transition_to(state);
    
    // set default mode
    mode = 2;   // ambient
}

Context::~Context()
{
    delete state_;
}

void Context::getobjects(Analog_in *Photocell, Analog_out *Led, Filter *filter, Timer *timer)
{
    photocell_ptr = Photocell;
    led_ptr = Led;
    filter_ptr = filter;
    timer_ptr = timer;
}

void Context::transition_to(State *state)
{
    Serial.println("Context: Transition");
    if (this->state_ != nullptr)
    {
        this->state_->on_exit();
        delete this->state_;
    }

    this->state_ = state;
    this->state_->set_context(this);
    this->state_->on_entry();
}

void Context::do_work()
{
    this->state_->on_do();
}

void Context::command_reset()
{
    this->state_->on_command_reset();
}

void Context::command_config_ambient()
{
    this->state_->on_command_config_ambient();
}

void Context::command_config_high()
{
    this->state_->on_command_config_high();
}

void Context::command_config_low()
{
    this->state_->on_command_config_low();
}

void Context::command_operation()
{
    this->state_->on_command_operation();
}

void Context::command_preoperation()
{
    this->state_->on_command_preoperation();
}

void Context::command_stop()
{
    this->state_->on_command_stop();
}