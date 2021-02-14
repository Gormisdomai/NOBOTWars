/* 
 * top level file for the Nobot
 */
#include "gpio_control.c"
#include "motor_control.h"

void setup()
{
    init_debug_leds();
    init_bat_sense();
    init_motor_interface();
    Serial.begin(115200);
}

byte counter = 0;

void loop()
{
    Serial.print(motor_write(counter));
    Serial.print("\t");
    Serial.println(counter++);
    delay(100);
}
