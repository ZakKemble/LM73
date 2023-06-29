// LM73 Temperature Sensor Library - https://github.com/ZakKemble/LM73
// Copyright (C) 2014-2023, Zak Kemble
// MIT License

#ifndef LM73_H_
#define LM73_H_

#include <Arduino.h>
#include <Wire.h>

class LM73
{
private:
	TwoWire &wire;
	uint8_t i2cAddress;
	uint8_t reg_config;
	void i2cRead(uint8_t* buf, uint8_t len);
	void i2cWrite(uint8_t* buf, uint8_t len);

public:
	LM73(TwoWire& wire): wire(wire) {};
	void begin(uint8_t address);
	void ctrl(
		uint8_t resolution,
		bool busTimeout
	);
	void mode(uint8_t mode);
	float temperature();
	void convert();
	bool available();
	uint8_t alertStatus();
	void alertReset();
	void alertConfig(
		bool enable,
		uint8_t polarity,
		float upperLimit,
		float lowerLimit
	);
};

#endif /* LM73_H_ */
