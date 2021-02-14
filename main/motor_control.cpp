/*
 * library for the gpio expander
*/
#include <Arduino.h>
#include <Wire.h>
#include "motor_control.h"

// address: 0100ABC where A=A0, B=A1, C=A2
#define GPIO_EXPANDER_ADDRESS (0b0100000)
#define GPIO_STATE_REGISTER (0x09)
#define GPIO_PINMODE_REGISTER (0x00)

/*
 * initialises motor control interface via I2C
*/
byte init_motor_interface()
{
    // with no address passed we assert our dominance as the I2C master
    Wire.begin();

    // set all pin modes to output
    Wire.beginTransmission(GPIO_EXPANDER_ADDRESS);

    byte bytes_to_send[2] = {GPIO_PINMODE_REGISTER, 0x00};
    Wire.write(bytes_to_send, 2);

    return Wire.endTransmission();
}


/*
 * writes a new output state byte for the motor control signals
*/
byte motor_write(byte new_state)
{
    Wire.beginTransmission(GPIO_EXPANDER_ADDRESS);

    byte bytes_to_send[2] = {GPIO_STATE_REGISTER, new_state};
    Wire.write(bytes_to_send, 2);

    return Wire.endTransmission();
}
