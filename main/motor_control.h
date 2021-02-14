#ifndef motor_control
#define montor_control

#include <Arduino.h>

byte init_motor_interface();
byte motor_write(byte new_state);

#endif