/*
 * Project: LM73 Temperature Sensor Library
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2014 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: https://github.com/zkemble/LM73
 */

/*
 * Multiple sensors
 *
 * A4 -> SDA (all sensors connect to the same Arduino pin)
 * A5 -> SCL (all sensors connect to the same Arduino pin)
 */

#include <LM73.h>
#include <Wire.h>

LM73 sensor1 = LM73();
LM73 sensor2 = LM73();
LM73 sensor3 = LM73();

void setup()
{
	Serial.begin(9600);

	setupSensor(LM73_0_I2C_FLOAT, sensor1); // LM73-0 with address pin not connected (floating)
	setupSensor(LM73_0_I2C_GND, sensor2); // LM73-0 with address pin connected to ground
	setupSensor(LM73_0_I2C_VDD, sensor3); // LM73-0 with address pin connected to power
}

static void setupSensor(LM73_i2caddr_t addr, LM73 sensor)
{
	sensor.begin(addr);
	sensor.setResolution(LM73_RESOLUTION_14BIT); // 14 bit
	sensor.power(LM73_POWER_ON); // Turn on sensor (continuous temperature conversion)
}

void loop()
{
	delay(1000);
	
	showSensorTemp(sensor1);
	showSensorTemp(sensor2);
	showSensorTemp(sensor3);

	Serial.println();
}

static void showSensorTemp(LM73 sensor)
{
	double temp = sensor.temperature();
	Serial.print("Temperature: ");
	Serial.println(temp, 5);
}
