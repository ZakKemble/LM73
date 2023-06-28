/*
 * Project: LM73 Temperature Sensor Library
 * Author: Zak Kemble
 * Copyright: (C) 2023 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: https://github.com/ZakKemble/LM73
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

LM73 lm73 = LM73(Wire);

void setup()
{
	Serial.begin(115200);
	Wire.begin();
	
	pinMode(2, INPUT_PULLUP);
	pinMode(13, OUTPUT);

	lm73.begin(0x48);
	lm73.ctrl(14, false); // 14-bit resolution, disable idle bus timeout
	lm73.mode(0); // Continuous mode
	lm73.alertConfig(true, 0, 30, 26); // Alert will trigger at 30C and stay triggered until temperature falls below 26C
}

void loop()
{
	delay(1000);

	// Get the latest temperature
	float temp = lm73.temperature();

	// Get alert state
	bool alertState = !digitalRead(2);

	// Show temperature
	Serial.print(F("Temperature: "));
	Serial.println(temp, 5);

	// Show alert state
	if(alertState)
	{
		Serial.println(F("ALERT!"));
		digitalWrite(13, HIGH);
	}
	else
	{
		Serial.println(F("OK"));
		digitalWrite(13, LOW);
	}

	Serial.println();
}
