/******************************************************************************
SparkFun_TCA9534.h
TCA9534 Arduino Library
Andy England @ SparkFun Electronics
March 3, 2020
https://github.com/sparkfun/Qwiic_RTC

Resources:
Uses Wire.h for i2c operation
Uses SPI.h for SPI operation

Development environment specifics:
Arduino IDE 1.6.4

This code is released under the [MIT License](http://opensource.org/licenses/MIT).
Please review the LICENSE.md file included with this example. If you have any questions 
or concerns with licensing, please contact techsupport@sparkfun.com.
Distributed as-is; no warranty is given.
******************************************************************************/

#pragma once

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>

//The 7-bit I2C address of the TCA9534
#define TCA9534_ADDR							0x27

#define REGISTER_INPUT_PORT          	 		0x00
#define REGISTER_OUTPUT_PORT          			0X01
#define REGISTER_INVERSION						0x02
#define REGISTER_CONFIGURATION        	 		0X03

#define GPIO_OUT								false
#define GPIO_IN									true

#define INVERT									true
#define NO_INVERT								false

class TCA9534
{
  public:
	
    TCA9534( void );

    bool begin(TwoWire &wirePort = Wire, uint8_t address = TCA9534_ADDR);
	
	bool pinMode(uint8_t gpioNumber, bool mode);
	bool pinMode(bool *gpioPinMode);

	bool invertPin(uint8_t gpioNumber, bool inversionMode);
	bool invertPin(bool *inversionMode);

	bool digitalWrite(uint8_t gpioNumber, bool value);
	bool digitalWrite(bool *gpioStatus);

	bool digitalRead(uint8_t gpioNumber);
	uint8_t digitalReadPort(bool *gpioStatus);

	bool readBit(uint8_t regAddr, uint8_t bitAddr);
	bool writeBit(uint8_t regAddr, uint8_t bitAddr, bool bitToWrite);
    uint8_t readRegister(uint8_t addr);
    bool writeRegister(uint8_t addr, uint8_t val);

private:
	uint8_t _gpioOutStatus = 0xFF;
	uint8_t _gpioInStatus;
	uint8_t _gpioPinMode = 0xFF;
	uint8_t _inversionStatus = 0;
	uint8_t _deviceAddress;
	TwoWire *_i2cPort;
};