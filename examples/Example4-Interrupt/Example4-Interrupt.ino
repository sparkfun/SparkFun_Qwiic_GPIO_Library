/******************************************************************************
  Qwiic Relay Example 4 - Interrupt
  Andy England @ SparkFun Electronics
  August 28, 2020
  https://github.com/sparkfun/Qwiic_GPIO
  Arduino 1.8.5

  The interrupt on the Qwiic GPIO is pulled low when there is a change on any input pin.
  The interrupt goes back high when the input register is read.
******************************************************************************/

#include <Wire.h>
#include "SparkFun_TCA9534.h"
/* I2C Command Byte Defines  */

TCA9534 myGPIO;

#define NUM_GPIO 8

#define INTERRUPT_PIN 13

bool currentPinMode[NUM_GPIO] = {GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN};

bool gpioStatus[NUM_GPIO];

bool dataReady = true;

void setup() {
  Serial.begin(115200);
  Serial.println("Qwiic GPIO Example 2b- Read GPIO Port");
  Wire.begin();
  if (myGPIO.begin() == false) {
    Serial.println("Check Connections. No Qwiic GPIO detected.");
    while (1);
  }
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  digitalWrite(INTERRUPT_PIN, HIGH);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), ISR, FALLING);
  myGPIO.pinMode(currentPinMode);//Use GPIO_OUT and GPIO_IN instead of OUTPUT and INPUT_PULLUP
}

void loop() {
  if (dataReady) {
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
    dataReady = false;
  }
}

void ISR() {
  dataReady = true;
}
