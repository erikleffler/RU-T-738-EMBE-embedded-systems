#pragma once
#include <Arduino.h>

/**
 * The base State class declares methods that all Concrete State should
 * implement and also provides a backreference to the Context object, associated
 * with the State. This backreference can be used by States to transition the
 * Context to another State.
 */

class Context;

class State
{
  /**
   * @var Context
   */

protected:
  Context *context_;

public:
  virtual ~State()
  {
  }

  void set_context(Context *context);

  virtual void on_do() = 0;
  virtual void on_entry() = 0;
  virtual void on_exit() = 0;
  virtual void on_command_reset() = 0;
  virtual void on_command_config_ambient() = 0;
  virtual void on_command_config_high() = 0;
  virtual void on_command_config_low() = 0;
  virtual void on_command_operation() = 0;
  virtual void on_command_preoperation() = 0;
  virtual void on_command_stop() = 0;

  // attributes
  int input_ph = 0;
  int filtered_input_ph = 0;
};