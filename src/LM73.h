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
	void i2cRead(uint8_t* buf, uint8_t const len) const;
	void i2cWrite(const uint8_t* const buf, uint8_t const len) const;

public:
	LM73(TwoWire& wire): wire(wire) {};
	void begin(uint8_t const address);
	void ctrl(
		uint8_t const resolution,
		bool const busTimeout
	) const;
	void mode(uint8_t const mode);
	float temperature() const;
	void convert() const;
	bool available() const;
	uint8_t alertStatus() const;
	void alertReset() const;
	void alertConfig(
		bool const enable,
		uint8_t const polarity,
		float const upperLimit,
		float const lowerLimit
	);
};

#endif /* LM73_H_ */
