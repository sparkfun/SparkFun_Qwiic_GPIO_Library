/******************************************************************************
  Qwiic Relay Example 1b - Write GPIO Block
  Andy England @ SparkFun Electronics
  August 28, 2020
  https://github.com/sparkfun/Qwiic_GPIO
  Arduino 1.8.5

  This sketch flips all 8 outputs on and off every second.

******************************************************************************/

#include <Wire.h>
#include "SparkFun_TCA9534.h"
/* I2C Command Byte Defines  */

TCA9534 myGPIO;

#define NUM_GPIO 8

bool currentPinMode[NUM_GPIO] = {GPIO_OUT, GPIO_OUT, GPIO_OUT, GPIO_OUT, GPIO_OUT, GPIO_OUT, GPIO_OUT, GPIO_OUT};

bool gpioConfig[NUM_GPIO] = {HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW};

void setup() {
  Serial.begin(115200);
  Serial.println("Qwiic GPIO Example 1b- Write GPIO Block");
  Wire.begin();
  if (myGPIO.begin() == false) {
    Serial.println("Check Connections. No Qwiic GPIO detected.");
    while (1);
  }

  myGPIO.pinMode(currentPinMode);//Use GPIO_OUT and GPIO_IN instead of OUTPUT and INPUT_PULLUP
}

void loop() {
  myGPIO.digitalWrite(gpioConfig);
  flipGPIO();
  delay(1000);
  myGPIO.digitalWrite(gpioConfig);
  flipGPIO();
  delay(1000);
}

void flipGPIO()
{
  for (uint8_t arrayPosition = 0; arrayPosition < NUM_GPIO; arrayPosition++)
  {
    gpioConfig[arrayPosition] = !gpioConfig[arrayPosition];
  }
}
