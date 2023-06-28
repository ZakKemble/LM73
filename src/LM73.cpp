/*
 * Project: LM73 Temperature Sensor Library
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2014 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: https://github.com/zkemble/LM73
 */

#include <Arduino.h>
#include <Wire.h>
#include "LM73.h"
#include "LM73_defs.h"
#include "LM73_config.h"

LM73::LM73()
{
}

void LM73::begin(LM73_i2caddr_t _i2cAddress)
{
	Wire.begin();
	i2cAddress = _i2cAddress;

	// TODO: do defaults here
}

bool LM73::i2cRead(uint8_t reg, uint8_t len, void* buff)
{
	Wire.beginTransmission(i2cAddress);
	Wire.write(reg); // Set pointer to register
	Wire.endTransmission(false); // Send data, but dont send STOP
	Wire.requestFrom((uint8_t)i2cAddress, (uint8_t)len); // Repeated START, read bytes, send STOP

	// TODO:
	// make sure endTransmission returned 0
	// make sure requestFrom returned len

	// Get the data
	byte idx = 0;
	while(Wire.available())
		((uint8_t*)buff)[idx++] = Wire.read();

	return true;
}

bool LM73::i2cWrite(uint8_t reg, uint8_t data)
{
	Wire.beginTransmission(i2cAddress);
	Wire.write(reg); // Set pointer to register
	Wire.write(data); // Set new data
	Wire.endTransmission(); // Send data and send STOP

	return true;
}

bool LM73::i2cWrite(uint8_t reg, uint8_t data, uint8_t data2)
{
	Wire.beginTransmission(i2cAddress);
	Wire.write(reg); // Set pointer to register
	Wire.write(data); // Set new data
	Wire.write(data2); // Set new data
	Wire.endTransmission(); // Send data and send STOP

	return true;
}

// Get temperature
#if !LM73_TINY_MODE
double LM73::temperature()
{
	uint8_t data[2];
	i2cRead(LM73_REG_TEMPERATURE, sizeof(data), data);
/*
	// TEST STUFF

	static byte aa = 255;
	aa++;
	if(aa == 0)
	{
		// 27.125   27
		//data2[0] = 0b00001101;
		//data2[1] = 0b10010000;
		data = 0b0000110110010000;
	}
	else if(aa == 1)
	{
		// -40.125   -40
		//data2[0] = 0b11101011;
		//data2[1] = 0b11110000;
		data = 0b1110101111110000;
	}
	else if(aa == 2)
	{
		// 0.125   0
		data = 0b0000000000010000;
	}
	else if(aa == 3)
	{
		// -0.625    -1
		data = 0b1111111110110000;
	}
	else
	{
		// -0.0625   0
		//data2[0] = 0b11111111;
		//data2[1] = 0b11111000;
		data = 0b1111111111111000;
		aa = 255;
	}
*/

	double temperature = ((data[0]<<8) | data[1]) * 0.0078125;
	return temperature;
}
#else
int16_t LM73::temperature()
{
	uint8_t data[2];
	i2cRead(LM73_REG_TEMPERATURE, sizeof(data), data);

	int16_t temperature = (data[0]<<8) | data[1];
	uint8_t doRound = data[1] & 0x40; // Is 0.5 bit set?

	if(temperature < 0)
	{
		doRound = !doRound;
		temperature = -((-temperature)>>7);
		if(doRound)
			temperature--;
	}
	else
	{
		temperature >>= 7;
		if(doRound)
			temperature++;
	}

	return temperature;
}
#endif

// Start a one shot conversion
void LM73::startOneShot()
{
	uint8_t reg;
	i2cRead(LM73_REG_CONFIG, sizeof(reg), &reg);
	reg |= LM73_BIT_ONE_SHOT;
	i2cWrite(LM73_REG_CONFIG, reg);
}

// Turn on/off
void LM73::power(LM73_power_t pwr)
{
	uint8_t reg;
	i2cRead(LM73_REG_CONFIG, sizeof(reg), &reg);
	reg = (reg & LM73_MASK_PD) | pwr;
	i2cWrite(LM73_REG_CONFIG, reg);
}

// Is one shot data ready?
bool LM73::ready()
{
	uint8_t reg;
	i2cRead(LM73_REG_CTRLSTATUS, sizeof(reg), &reg);
	return reg & LM73_BIT_DAV_FLAG;
}

// Set temperature resolution
void LM73::setResolution(LM73_resolution_t resolution)
{
	uint8_t reg;
	i2cRead(LM73_REG_CTRLSTATUS, sizeof(reg), &reg);
	reg = (reg & LM73_MASK_RESOLUTION) | resolution;
	i2cWrite(LM73_REG_CTRLSTATUS, reg);
}

// 
#if !LM73_TINY_MODE
void LM73::setAlert(double high, double low)
{
	// NOTE: Alert temperatures are only 11 bit

	uint16_t h = high / 0.0078125;
	uint16_t l = low / 0.0078125;

	// TODO: Check neg numbers!

	i2cWrite(LM73_REG_THI, h>>8, h & 0xE0);
	i2cWrite(LM73_REG_TLOW, l>>8, l & 0xE0);
}
#else
void LM73::setAlert(int16_t high, int16_t low)
{
	uint16_t h = high << 7;
	uint16_t l = low << 7;
	
	// TODO: Check neg numbers!

	i2cWrite(LM73_REG_THI, h>>8, h & 0xE0);
	i2cWrite(LM73_REG_TLOW, l>>8, l & 0xE0);
}
#endif
