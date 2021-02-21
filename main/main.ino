/* 
 * top level file for the Nobot
 */
#include "gpio_control.c"
#include "wifi_read.h"
#include "motor_control.h"

void setup()
{
    init_debug_leds();
    init_bat_sense();
    init_motor_interface();
    init_wifi_server();
    Serial.begin(115200);
}

char input_buff[10];
bool led1 = false;
bool led2 = false;
bool led3 = false;

void loop()
{
    // comment/uncomment to enable serial control
    /*
    while (!Serial.available());
    byte index = 0;
    while (Serial.available() > 0)
    {
      input_buff[index++] = (char)Serial.read();
      delay(10);
    }
    index--;
    while (index < sizeof(input_buff))
    {
      input_buff[index++] = ' ';
    }
    Serial.print("command: ");
    Serial.println(input_buff);
    Serial.print("outcome: ");
    char command = input_buff[0];
    */

    // comment/uncomment to enable wifi control
    char command = wifi_server_loop();
    if (command == '_') return;
    switch(command)
    {
      case 's':
        motor_write(0xFF);
        Serial.println("stop");
        break;
      case 'f':
        motor_write(0x9F);
        Serial.println("forward");
        break;
      case 'b':
        motor_write(0x6F);
        Serial.println("backward");
        break;
      case 'l':
        motor_write(0x5F);
        Serial.println("left");
        break;
      case 'r':
        motor_write(0xAF);
        Serial.println("right");
        break;
      case 'c':
        motor_write(0x0F);
        Serial.println("coast");
        break;
      case 'v':
        Serial.print("Vbat: ");
        Serial.print(read_bat_voltage());
        Serial.println("V");
        break;
      case 'q':
        led1 = !led1;
        Serial.println(led1);
        digitalWrite(DEBUG_LED_0, led1);
        break;
      case 'w':
        led2 = !led2;
        Serial.println(led2);
        digitalWrite(DEBUG_LED_1, led2);
        break;
      case 'e':
        led3 = !led3;
        Serial.println(led3);
        digitalWrite(DEBUG_LED_2, led3);
        break;
      default:
        Serial.println("unrecognised!");
    }
}
