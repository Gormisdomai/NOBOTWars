#ifndef motor_control
#define montor_control

#include <Arduino.h>

byte init_motor_interface();
byte motor_write(byte new_state);

enum motor_state
{
  motor_coast,
  motor_forward,
  motor_backward,
  motor_brake
};

motor_state mov_A = motor_brake;
motor_state mov_B = motor_brake;
motor_state wep_A = motor_brake;
motor_state wep_B = motor_brake;

enum move_state
{
  brake,
  forward,
  backward,
  left,
  right,
  coast
};

#endif
