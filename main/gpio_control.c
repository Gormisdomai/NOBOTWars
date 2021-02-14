/* 
 * library for the Nobot's gpio control
*/
#include <arduino.h>

#define DEBUG_LED_0 (14)
#define DEBUG_LED_1 (12)
#define DEBUG_LED_2 (13)

#define BAT_SENSE_ENABLE (16)
#define BAT_SENSE_INPUT (A0)
#define BAT_SENSE_R1_KOHMS (float)(10)
#define BAT_SENSE_R2_KOHMS (float)(39)
#define BAT_RESISTOR_GAIN (BAT_SENSE_R1_KOHMS/(BAT_SENSE_R1_KOHMS + BAT_SENSE_R2_KOHMS))
#define ADC_STEPS (1024)
#define FUDGE_FACTOR (float)(1.02) //I should probably have used sense resistors with a better tolerance!!
#define BAT_SENSE_GAIN (BAT_RESISTOR_GAIN * ADC_STEPS * FUDGE_FACTOR)

/*
 * initialises pin modes and states of debug LED pins
*/
void init_debug_leds()
{
    pinMode(DEBUG_LED_0, OUTPUT);
    pinMode(DEBUG_LED_1, OUTPUT);
    pinMode(DEBUG_LED_2, OUTPUT);

    digitalWrite(DEBUG_LED_0, LOW);
    digitalWrite(DEBUG_LED_1, LOW);
    digitalWrite(DEBUG_LED_2, LOW);
}

/*
 * initalises pin modes and states of battery sense circuit
*/
void init_bat_sense()
{
    pinMode(BAT_SENSE_ENABLE, OUTPUT);
    pinMode(BAT_SENSE_INPUT, INPUT);

    digitalWrite(BAT_SENSE_ENABLE, LOW);
}

/*
 * reads the battery voltage, returning a value in volts
*/
float read_bat_voltage()
{
    // enable bat sense
    digitalWrite(BAT_SENSE_ENABLE, HIGH);
    // wait a mo - time constant is roughly 1 ms so wait a while for voltage to stabilise
    delay(10);
    // read value
    unsigned int reading = analogRead(BAT_SENSE_INPUT);
    // disable bat sense
    digitalWrite(BAT_SENSE_ENABLE, LOW);
    // convert reading to volts and return it
    return (float)reading / BAT_SENSE_GAIN;
    // return (float)reading / BAT_SENSE_GAIN;
}