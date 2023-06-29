// LM73 Temperature Sensor Library - https://github.com/ZakKemble/LM73
// Copyright (C) 2014-2023, Zak Kemble
// MIT License

/*
 * Low-power one-shot temperature conversion
 *
 * A4 -> SDA
 * A5 -> SCL
 * 2 -> ALM
 */

#include <LM73.h>
#include <Wire.h>

LM73 lm73 = LM73(Wire);

void setup()
{
	Serial.begin(115200);
	Wire.begin();

	lm73.begin(0x48); // LM73-0 with floating address pin
	lm73.ctrl(14, false); // 14-bit resolution, disable idle bus timeout
	lm73.mode(1); // Low-power one-shot mode
}

void loop()
{
	delay(1000);

	Serial.println(F("Starting one-shot conversion..."));

	// Begin one-shot conversion 
	lm73.convert();

	// Start timing conversion
	byte start = millis();

	// Wait for completion
	while(!lm73.available());

	// Workout conversion time
	byte time = ((byte)millis()) - start;

	// Get the temperature
	float temp = lm73.temperature();

	Serial.print(F("Conversion time: "));
	Serial.println(time);

	Serial.print(F("Temperature: "));
	Serial.println(temp, 5);

	Serial.println();
}
