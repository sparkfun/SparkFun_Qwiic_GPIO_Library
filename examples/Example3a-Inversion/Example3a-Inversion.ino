/******************************************************************************
  Qwiic Relay Example 3a - Inversion
  Andy England @ SparkFun Electronics
  August 28, 2020
  https://github.com/sparkfun/Qwiic_GPIO
  Arduino 1.8.5

  This sketch shows how to invert the input signal on a pin

******************************************************************************/

#include <Wire.h>
#include "SparkFun_TCA9534.h"
/* I2C Command Byte Defines  */

TCA9534 myGPIO;

void setup() {
  Serial.begin(115200);
  Serial.println("Qwiic GPIO Example 3a- Inversion");
  Wire.begin();
  if (myGPIO.begin() == false) {
    Serial.println("Check Connections. No Qwiic GPIO detected.");
    while (1);
  }

  myGPIO.pinMode(0, GPIO_IN);//Use GPIO_OUT and GPIO_IN instead of OUTPUT and INPUT_PULLUP
  
  //Note that inversion of a pin only works on the input register.
  myGPIO.invertPin(0, INVERT);
  //myGPIO.invertPin(0, NO_INVERT); //Uncomment this line to remove the logic inversion on pin 0.
}

void loop() {
  bool status = myGPIO.digitalRead(0);    
  switch (status)
    {
      case true:
        Serial.println("GPIO 0: HI");
        break;
      case false:
        Serial.println("GPIO 0: LO");
        break;
    }
  delay(100);
}
