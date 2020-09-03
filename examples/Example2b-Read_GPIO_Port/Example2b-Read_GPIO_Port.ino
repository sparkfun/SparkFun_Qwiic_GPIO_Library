/******************************************************************************
  Qwiic Relay Example 2b- Read GPIO Port
  Andy England @ SparkFun Electronics
  August 28, 2020
  https://github.com/sparkfun/Qwiic_GPIO
  Arduino 1.8.5

  This sketch allows the user to read the status of all 8 GPIO simultaneously

******************************************************************************/

#include <Wire.h>
#include "SparkFun_TCA9534.h"
/* I2C Command Byte Defines  */

TCA9534 myGPIO;

#define NUM_GPIO 8

bool currentPinMode[NUM_GPIO] = {GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN};

bool gpioStatus[NUM_GPIO];

void setup() {
  Serial.begin(115200);
  Serial.println("Qwiic GPIO Example 2b- Read GPIO Port");
  Wire.begin(23, 22);
  if (myGPIO.begin() == false) {
    Serial.println("Check Connections. No Qwiic GPIO detected.");
    while (1);
  }

  myGPIO.pinMode(currentPinMode);//Use GPIO_OUT and GPIO_IN instead of OUTPUT and INPUT_PULLUP
}

void loop() {
  //There are two ways to read from a port, either by returning the full register value as a uint8_t, or passing in an array of 8 boolean's to be modified by the function with the statuses of each pin
  uint8_t portValue = myGPIO.digitalReadPort(gpioStatus);

  Serial.print("uint8_t: ");
  Serial.println(portValue, BIN);
  Serial.print("Bool array: ");
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
  Serial.println("\n");
  delay(100);
}
