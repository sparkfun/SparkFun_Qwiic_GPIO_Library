/******************************************************************************
  Qwiic Relay Example 1a - Write GPIO
  Andy England @ SparkFun Electronics
  August 28, 2020
  https://github.com/sparkfun/Qwiic_GPIO
  Arduino 1.8.5

  This sketch sets up a GPIO 0 as an output and toggles
  the output HIGH and LOW.

  This device sinks current. When an output is LOW then current will flow.

******************************************************************************/

#include <Wire.h>
#include "SparkFun_TCA9534.h"
/* I2C Command Byte Defines  */

TCA9534 myGPIO;

void setup() {
  Serial.begin(115200);
  Serial.println("Qwiic GPIO Example 1a- Write GPIO");
  Wire.begin();
  if (myGPIO.begin() == false) {
    Serial.println("Check Connections. No Qwiic GPIO detected.");
    while (1);
  }

  myGPIO.pinMode(0, GPIO_OUT);//Use GPIO_OUT and GPIO_IN instead of OUTPUT and INPUT_PULLUP
}

void loop() {
  myGPIO.digitalWrite(0, HIGH);
  Serial.println("HIGH");
  delay(1000);
  myGPIO.digitalWrite(0, LOW);
  Serial.println("LOW");
  delay(1000);
}
