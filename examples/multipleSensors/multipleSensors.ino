// LM73 Temperature Sensor Library - https://github.com/ZakKemble/LM73
// Copyright (C) 2014-2023, Zak Kemble
// MIT License

/*
 * Multiple sensors
 *
 * A4 -> SDA (all sensors connect to the same Arduino pin)
 * A5 -> SCL (all sensors connect to the same Arduino pin)
 */

#include <LM73.h>
#include <Wire.h>

LM73 sensor1 = LM73(Wire);
LM73 sensor2 = LM73(Wire);
LM73 sensor3 = LM73(Wire);

void setup()
{
	Serial.begin(115200);
	Wire.begin();

	setupSensor(0x48, sensor1); // LM73-0 with address pin not connected (floating)
	setupSensor(0x49, sensor2); // LM73-0 with address pin connected to ground
	setupSensor(0x4A, sensor3); // LM73-0 with address pin connected to power
}

static void setupSensor(byte addr, LM73& sensor)
{
	sensor.begin(addr);
	sensor.ctrl(14, false); // 14-bit resolution, disable idle bus timeout
	sensor.mode(0); // Continuous mode
}

void loop()
{
	delay(1000);
	
	showSensorTemp(sensor1);
	showSensorTemp(sensor2);
	showSensorTemp(sensor3);

	Serial.println();
}

static void showSensorTemp(LM73& sensor)
{
	float temp = sensor.temperature();
	Serial.print(F("Temperature: "));
	Serial.println(temp, 5);
}
