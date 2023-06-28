/*
 * Project: LM73 Temperature Sensor Library
 * Author: Zak Kemble
 * Copyright: (C) 2023 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: https://github.com/ZakKemble/LM73
 */

#include <Arduino.h>
#include <Wire.h>
#include "LM73.h"
#include "LM73_defs.h"

void LM73::i2cRead(uint8_t* buf, uint8_t len)
{
	wire.beginTransmission(i2cAddress);
	wire.write(buf[0]); // Set pointer to register
	wire.endTransmission(false); // Send data, but dont send STOP
	wire.requestFrom(i2cAddress, len); // Repeated START, read bytes, send STOP

	// TODO:
	// make sure endTransmission returned 0
	// make sure requestFrom returned len

	// Get the data
	while(wire.available())
		*buf++ = wire.read();
}

void LM73::i2cWrite(uint8_t* buf, uint8_t len)
{
	wire.beginTransmission(i2cAddress);
	wire.write(buf, len);
	wire.endTransmission();
}

void LM73::begin(uint8_t address)
{
	i2cAddress = address;
	reg_config = 0;
}

void LM73::ctrl(uint8_t resolution, uint8_t timeoutDisable)
{
	uint8_t buf[2];
	buf[0] = LM73_REG_CTRLSTATUS;
	buf[1] = (timeoutDisable<<LM73_BIT_TIMEOUT_DIS) | ((resolution - 11)<<LM73_BIT_TEMP_RES);
	i2cWrite(buf, sizeof(buf));
}

void LM73::mode(uint8_t mode)
{
	// 0 = continous
	// 1 = one shot

	reg_config = (reg_config & (1<<LM73_BIT_PWR_DOWN)) | (mode<<LM73_BIT_PWR_DOWN);

	uint8_t buf[2];
	buf[0] = LM73_REG_CONFIG;
	buf[1] = reg_config;
	i2cWrite(buf, sizeof(buf));
}

/*
int32_t LM73::temperature()
{
	uint8_t data[2];
	i2cRead(LM73_REG_TEMPERATURE, sizeof(data), data);

	int16_t temperature = (data[0]<<8) | data[1];
	temperature >>= 7; // Sign extend and remove fractional part

	int32_t t = temperature * 100000;
	uint32_t frac = 0;
	if(data[1] & (1<<6)) frac += 50000;
	if(data[1] & (1<<5)) frac += 25000;
	if(data[1] & (1<<4)) frac += 12500;
	if(data[1] & (1<<3)) frac += 6250;
	if(data[1] & (1<<2)) frac += 3125;
	t += frac;

	return t;
}
*/
float LM73::temperature()
{
	uint8_t buf[2];
	buf[0] = LM73_REG_TEMPERATURE;
	i2cRead(buf, sizeof(buf));
	return ((buf[0]<<8) | buf[1]) / 128.0;
}

void LM73::convert()
{
	uint8_t buf[2];
	buf[0] = LM73_REG_CONFIG;
	buf[1] = reg_config | (1<<LM73_BIT_ONE_SHOT);
	i2cWrite(buf, sizeof(buf));
}

bool LM73::available()
{
	uint8_t buf = LM73_REG_CTRLSTATUS;
	i2cRead(&buf, sizeof(buf));
	return buf & (1<<LM73_BIT_DAV_FLAG);
}

uint8_t LM73::alertStatus()
{
	uint8_t buf = LM73_REG_CTRLSTATUS;
	i2cRead(&buf, sizeof(buf));
	return (buf & 0b1110);
}

void LM73::alertReset()
{
	uint8_t buf[2];
	buf[0] = LM73_REG_CONFIG;
	buf[1] = reg_config | (1<<LM73_BIT_ALRT_RST);
	i2cWrite(buf, sizeof(buf));
}

void LM73::alertConfig(
	bool enable,
	uint8_t polarity,
	float upperLimit,
	float lowerLimit
)
{
	// NOTE: Alert temperatures are only 11 bit

	uint8_t buf[3];

	int16_t tmp;

	tmp = upperLimit * 128;
	buf[0] = LM73_REG_THI;
	buf[1] = tmp>>8;
	buf[2] = tmp;
	i2cWrite(buf, 3);
	

	tmp = lowerLimit * 128;
	buf[0] = LM73_REG_TLOW;
	buf[1] = tmp>>8;
	buf[2] = tmp;
	i2cWrite(buf, 3);

	reg_config = (reg_config & ~((1<<LM73_BIT_ALRT_EN)|(1<<LM73_BIT_ALRT_POL))) | (!enable<<LM73_BIT_ALRT_EN) | (polarity<<LM73_BIT_ALRT_POL);

	buf[0] = LM73_REG_CONFIG;
	buf[1] = reg_config;
	i2cWrite(buf, 2);


/*
	uint16_t hfrac = upperLimit % 100000;
	uint16_t lfrac = lowerLimit % 100000;
	
	uint8_t hd = 0;
	if(hfrac > 50000) hd |= (1<<6);
	if((hfrac - 50000) > 25000) hd |= (1<<5);
	
	uint8_t ld = 0;
	if(lfrac > 50000) ld |= (1<<6);
	if((lfrac - 50000) > 25000) ld |= (1<<5);
	
	int16_t upper = upperLimit ;
	hd |= (upper & 1) << 7;
	upper >>= 1;
	
	int16_t lower = lowerLimit ;
	ld |= (lower & 1) << 7;
	lower >>= 1;
	
	i2cWrite(LM73_REG_THI, upper, hd);
	i2cWrite(LM73_REG_TLOW, lower, ld);
*/
}
