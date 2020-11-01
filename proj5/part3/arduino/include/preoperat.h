#include <analog_out.h>
#include <filter.h>
#include <context.h>

/**
 * Concrete States implement various behaviors, associated with a state of the
 * Context.
 */

class Preoperational_state : public State
{
public:
  void on_do() override;
  void on_entry() override;
  void on_exit() override; 
  void on_command_reset() override;
  void on_command_config_ambient() override;
  void on_command_config_high() override;
  void on_command_config_low() override;
  void on_command_operation() override;
  void on_command_preoperation() override {};
  void on_command_stop() override;
};