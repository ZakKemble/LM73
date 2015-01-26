/*
 * Project: LM73 Temperature Sensor Library
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2014 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: https://github.com/zkemble/LM73
 */

/*
 * Alert
 *
 * A4 -> SDA
 * A5 -> SCL
 * 2 -> ALM
 */

#include <LM73.h>
#include <Wire.h>

LM73 lm73 = LM73();

void setup()
{
	Serial.begin(9600);

	lm73.begin(LM73_0_I2C_FLOAT);
	lm73.setResolution(LM73_RESOLUTION_14BIT); // 14 bit
	lm73.power(LM73_POWER_ON); // Turn on sensor (continuous temperature conversion)
	lm73.setAlert(30, 28); // Alert will trigger at 30C and stay triggered until temperature falls below 28C
}

void loop()
{
	delay(1000);

	// Get the temperature
	double temp = lm73.temperature();

	// Get alert state
	bool alertState = !digitalRead(2);

	// Show temperature
	Serial.print("Temperature: ");
	Serial.println(temp, 5);

	// Show alert state
	if(alertState)
		Serial.println("ALERT!");
	else
		Serial.println("OK");

	Serial.println();
}
