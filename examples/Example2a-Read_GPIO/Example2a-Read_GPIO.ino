/******************************************************************************
  Qwiic Relay Example 2a - Read GPIO
  Andy England @ SparkFun Electronics
  August 28, 2020
  https://github.com/sparkfun/Qwiic_GPIO
  Arduino 1.8.5

  This sketch allows the user to read a value from GPIO 0

******************************************************************************/

#include <Wire.h>
#include "SparkFun_TCA9534.h"
/* I2C Command Byte Defines  */

TCA9534 myGPIO;

void setup() {
  Serial.begin(115200);
  Serial.println("Qwiic GPIO Example 2a- Read GPIO");
  Wire.begin();
  if (myGPIO.begin() == false) {
    Serial.println("Check Connections. No Qwiic GPIO detected.");
    while (1);
  }

  myGPIO.pinMode(0, GPIO_IN);//Use GPIO_OUT and GPIO_IN instead of OUTPUT and INPUT_PULLUP
}

void loop() {
  bool gpioState = myGPIO.digitalRead(0);
  switch (gpioState) {
    case true:
      Serial.println("HIGH");
      break;
    case false:
      Serial.println("LOW");
      break;
  }
  delay(250);
}
