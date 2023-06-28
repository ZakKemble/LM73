/*
 * Project: LM73 Temperature Sensor Library
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2014 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: https://github.com/zkemble/LM73
 */

#ifndef LM73_H_
#define LM73_H_

#include <Arduino.h>
#include "LM73_defs.h"
#include "LM73_config.h"

/**
 * \enum LM73_i2caddr_t 
 * \brief I2C Address
 */
typedef enum
{
	// LM73-0
	LM73_0_I2C_FLOAT = 0x48, // Float
	LM73_0_I2C_GND = 0x49, // Ground
	LM73_0_I2C_VDD = 0x4A, // VDD

	// LM73-1
	LM73_1_I2C_FLOAT = 0x4C, // Float
	LM73_1_I2C_GND = 0x4D, // Ground
	LM73_1_I2C_VDD = 0x4E, // VDD
} LM73_i2caddr_t;

/**
 * \enum LM73_resolution_t 
 * \brief Temperature resolution
 */
typedef enum
{
	LM73_RESOLUTION_11BIT = 0b00000000,
	LM73_RESOLUTION_12BIT = 0b00100000,
	LM73_RESOLUTION_13BIT = 0b01000000,
	LM73_RESOLUTION_14BIT = 0b01100000
} LM73_resolution_t;

/**
 * \enum LM73_power_t 
 * \brief Power mode
 */
typedef enum
{
	LM73_POWER_ON = 0b00000000,
	LM73_POWER_OFF = 0b10000000,
} LM73_power_t;

class LM73
{
private:
	LM73_i2caddr_t i2cAddress;

	bool i2cRead(uint8_t reg, uint8_t len, void* buff);
	bool i2cWrite(uint8_t reg, uint8_t data);
	bool i2cWrite(uint8_t reg, uint8_t data, uint8_t data2);

public:
	LM73();
	
	void begin(LM73_i2caddr_t address);

/**
* Get temperature
*
* @return The temperature
*/
#if !LM73_TINY_MODE
	double temperature();
#else
	int16_t temperature();
#endif

/**
* See if one shot temperature conversion is complete
*
* @return false if not ready, true otherwise
*/
	bool ready();

/**
* Begin a one shot temperature convertion
*
* @return (none)
*/
	void startOneShot();

/**
* Set temperature resolution, lower resolution = faster convertion time
*
* @param [resolution] The resolution
* @return (none)
*/
	void setResolution(LM73_resolution_t resolution);

/**
* Set alarm temperature
*
* @param [high] Trigger temperature
* @param [low] Reset temperature
* @return (none)
*/
#if !LM73_TINY_MODE
	void setAlert(double high, double low);
#else
	void setAlert(int16_t high, int16_t low);
#endif

/**
* Set power mode
*
* @param [pwr] Power mode
* @return (none)
*/
	void power(LM73_power_t pwr);
};

#endif /* LM73_H_ */
