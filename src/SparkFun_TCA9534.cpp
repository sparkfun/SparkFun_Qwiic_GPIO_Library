 /******************************************************************************
SparkFun_TCA9534.h
SparkFun Qwiic GPIO (TCA9534) Arduino Library
Andy England @ SparkFun Electronics
March 3, 2020
https://github.com/sparkfun/SparkFun_Qwiic_GPIO_Arduino_Library

Development environment specifics:
Arduino IDE 1.6.4

This code is released under the [MIT License](http://opensource.org/licenses/MIT).
Please review the LICENSE.md file included with this example. If you have any questions
or concerns with licensing, please contact techsupport@sparkfun.com.
Distributed as-is; no warranty is given.
******************************************************************************/

#include "SparkFun_TCA9534.h"

TCA9534::TCA9534( void )
{

}

bool TCA9534::begin(TwoWire &wirePort, uint8_t address)
{
	_deviceAddress = address;
	_i2cPort = &wirePort;
	
	_i2cPort->beginTransmission(_deviceAddress);
	
    if (_i2cPort->endTransmission() != 0)
	{
      return (false); //Error: Sensor did not ack
	}
	return(true);
}

bool TCA9534::pinMode(uint8_t gpioNumber, bool mode)
{
	_gpioPinMode &= ~(1 << gpioNumber);
	_gpioPinMode |= mode << gpioNumber;
	return writeRegister(REGISTER_CONFIGURATION, _gpioPinMode);
}

bool TCA9534::pinMode(bool *gpioPinMode)
{
	_gpioPinMode = 0;
	for (uint8_t bitPosition = 0; bitPosition < 8; bitPosition++)
	{
		_gpioPinMode |= gpioPinMode[bitPosition] << bitPosition;
	}
	return writeRegister(REGISTER_CONFIGURATION, _gpioPinMode);
}

bool TCA9534::invertPin(uint8_t gpioNumber, bool inversionMode)
{
	_inversionStatus &= ~(1 << gpioNumber);
	_inversionStatus |= inversionMode << gpioNumber;
	return writeRegister(REGISTER_INVERSION, _inversionStatus);
}

bool TCA9534::invertPin(bool *inversionMode)
{
	_inversionStatus = 0;
	for (uint8_t bitPosition = 0; bitPosition < 8; bitPosition++)
	{
		_inversionStatus |= inversionMode[bitPosition] << bitPosition;
	}
	return writeRegister(REGISTER_INVERSION, _inversionStatus);
}

bool TCA9534::digitalWrite(uint8_t gpioNumber, bool value)
{
	_gpioOutStatus &= ~(1 << gpioNumber);
	_gpioOutStatus |= value << gpioNumber;
	return writeRegister(REGISTER_OUTPUT_PORT, _gpioOutStatus);
}

bool TCA9534::digitalWrite(bool *gpioOutStatus)
{
	_gpioOutStatus = 0; 
	for (uint8_t bitPosition = 0; bitPosition < 8; bitPosition++)
	{
		_gpioOutStatus |= gpioOutStatus[bitPosition] << bitPosition;
	}
	return writeRegister(REGISTER_OUTPUT_PORT, _gpioOutStatus);
}

bool TCA9534::digitalRead(uint8_t gpioNumber)
{
	_gpioInStatus = readRegister(REGISTER_INPUT_PORT);
	return _gpioInStatus & (1 << gpioNumber);
}

uint8_t TCA9534::digitalReadPort(bool *gpioInStatus)
{
	
	_gpioInStatus = readRegister(REGISTER_INPUT_PORT);
	for (uint8_t bitPosition = 0; bitPosition < 8; bitPosition++)
	{
		gpioInStatus[bitPosition] = _gpioInStatus & (1 << bitPosition);
	}
	return _gpioInStatus;
}

bool TCA9534::readBit(uint8_t regAddr, uint8_t bitAddr)
{
	return ((readRegister(regAddr) & (1 << bitAddr)) >> bitAddr);
}

bool TCA9534::writeBit(uint8_t regAddr, uint8_t bitAddr, bool bitToWrite)
{
	_gpioOutStatus &= ~(1 << bitAddr);
	_gpioOutStatus |= bitToWrite << bitAddr;
	return writeRegister(regAddr, _gpioOutStatus);
}

uint8_t TCA9534::readRegister(uint8_t addr)
{
	_i2cPort->beginTransmission(_deviceAddress);
	_i2cPort->write(addr);
	_i2cPort->endTransmission();

    //typecasting the 1 parameter in requestFrom so that the compiler
    //doesn't give us a warning about multiple candidates
    if (_i2cPort->requestFrom(static_cast<uint8_t>(_deviceAddress), static_cast<uint8_t>(1)) != 0)
    {
        return _i2cPort->read();
    }
	return false;
}

bool TCA9534::writeRegister(uint8_t addr, uint8_t val)
{
	_i2cPort->beginTransmission(_deviceAddress);
	_i2cPort->write(addr);
	_i2cPort->write(val);
    if (_i2cPort->endTransmission() != 0)
      return (false); //Error: Sensor did not ack
	return(true);
}