/*
 * Project: LM73 Temperature Sensor Library
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2014 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: https://github.com/zkemble/LM73
 */

/*
 * Low power one shot temperature convertion
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
	lm73.power(LM73_POWER_OFF); // Turn off sensor (one shot temperature convertion)
}

void loop()
{
	delay(1000);

	Serial.println("Starting one shot convertion...");

	// Begin one shot convertion 
	// Don't turn on sensor, that's done automatically
	lm73.startOneShot();

	// Start timing convertion
	byte start = millis();

	// Wait for completion
	while(!lm73.ready());

	// Workout convertion time
	byte time = ((byte)millis()) - start;

	// Get the temperature
	double temp = lm73.temperature();

	Serial.print("Convertion time: ");
	Serial.println(time);

	Serial.print("Temperature: ");
	Serial.println(temp, 5);

	Serial.println();
}
