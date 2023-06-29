# LM73 Temperature Sensor Library

[TI LM73](https://www.ti.com/product/LM73) Temperature sensor IC library for Arduino.

## Installing

Search for "LM73" in the Arduino library manager and check out some of the examples!

## Docs

|Method|Parameters|Returns|Description|
|---|---|---|---|
|LM73(<br>TwoWire& wire<br>)|**wire**:<br>I2C interface to use.<br>Valid values: `Wire`, `Wire1`, `Wire2` ... etc.|Instance of LM73|Constructor.|
|begin(<br>uint8_t address<br>)|**address**:<br>Sensor I2C Address<br>Valid values: see table below|void|Initializes instance.|
|ctrl(<br>uint8_t resolution,<br>bool busTimeout<br>)|**resolution**:<br>Temperature conversion resolution.<br>Lower resolution gives faster conversion times.<br>Valid values: `11`, `12`, `13` or `14`<br>**busTimeout**:<br>This is an SMBus feature.<br>It's usually best to disable it (`false`) to reduce power consumption.|void|Configure various parameters.|
|mode(<br>uint8_t mode<br>)|**mode**:<br>`0` = Continuous (default)<br>`1` = Low-power one-shot|void|Set conversion mode.|
|read()|-|**float**: The temperature|Reads the latest temperature conversion.|
|convert()|-|void|Start a new one-shot conversion.<br>Has no effect in continuous mode.|
|available()|-|**bool**:<br>`true`: One-shot conversion complete.<br>`false`: Busy|-|
|alertStatus()|-|**uint8_t**:<br>Bitwise state and flags<br>Bit 7-4: N/A<br>Bit 3: Alert status<br>Bit 2: High flag<br>Bit 1: Low flag<br>Bit 0: N/A|Reads alarm status and high/low temperature flags.<br>See datasheet for more info.|
|alertReset()|-|void|Clear alarm output.|
|alertConfig(<br>bool enable,<br>uint8_t polarity,<br>float upperLimit,<br>float lowerLimit<br>)|**enable**:<br>Enable alarm output.<br>**polarity**:<br>`0` = Active low (default).<br>`1` = Active high.<br>**upperLimit**:<br>Alarm trigger level.<br>**lowerLimit**:<br>Alarm clear level.|void|-|

## Device I2C Addresses

The I2C address of the sensor IC will depend on whether it's an `-0` or `-1` type and the state of its address pin.

|Address pin|LM73-0|LM73-1|
|---|---|---|
|Float|0x48|0x4C|
|Ground|0x49|0x4D|
|VDD|0x4A|0x4E|
