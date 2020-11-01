#pragma once
#include <Arduino.h>
#include <state.h>
#include <analog_in.h>
#include <analog_out.h>
#include <filter.h>
#include <timer.h>

class State;

class Context
{
private:
  State *state_;

public:
  // constructor
  Context(State *state);
  // destructor
  ~Context();

  // methods
  void transition_to(State *state); // The Context allows changing the State object at runtime
  void do_work(); // The Context delegates part of its behavior to the current State object.
  void command_reset();
  void command_config_ambient();
  void command_config_high();
  void command_config_low();
  void command_operation();
  void command_preoperation();
  void command_stop();
  void getobjects(Analog_in *Photocell, Analog_out *Led, Filter *filter, Timer *timer);

  //ptr
  Analog_in *photocell_ptr;
  Analog_out *led_ptr;
  Filter *filter_ptr;
  Timer *timer_ptr;

  // attributes
  int8_t mode;
  bool last_was_operational;
};