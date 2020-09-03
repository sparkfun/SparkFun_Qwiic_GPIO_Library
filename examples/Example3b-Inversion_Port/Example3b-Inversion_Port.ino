/******************************************************************************
  Qwiic Relay Example 3b - Inversion Port
  Andy England @ SparkFun Electronics
  August 28, 2020
  https://github.com/sparkfun/Qwiic_GPIO
  Arduino 1.8.5

  This sketch shows how to invert the input signal on multiple pins

******************************************************************************/

#include <Wire.h>
#include "SparkFun_TCA9534.h"
/* I2C Command Byte Defines  */

TCA9534 myGPIO;

#define NUM_GPIO 8

bool currentPinMode[NUM_GPIO] = {GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN};

bool inversionStatus[NUM_GPIO] = {INVERT, INVERT, INVERT, INVERT, NO_INVERT, NO_INVERT, NO_INVERT, NO_INVERT};

bool gpioStatus[NUM_GPIO];

void setup() {
  Serial.begin(115200);
  Serial.println("Qwiic GPIO Example 3- Inversion");
  Wire.begin(23, 22);
  if (myGPIO.begin() == false) {
    Serial.println("Check Connections. No Qwiic GPIO detected.");
    while (1);
  }

  myGPIO.pinMode(currentPinMode);

  //Note that inversion of a pin only works on the input register.
  myGPIO.invertPin(inversionStatus);
}

void loop() {
  myGPIO.digitalReadPort(gpioStatus);
  for (uint8_t arrayPosition = 0; arrayPosition < NUM_GPIO; arrayPosition++) {
    Serial.print(arrayPosition);
    Serial.print(": ");
    switch (gpioStatus[arrayPosition])
    {
      case true:
        Serial.print("HI ");
        break;
      case false:
        Serial.print("LO ");
        break;
    }
  }
  Serial.println();
  delay(100);
}
