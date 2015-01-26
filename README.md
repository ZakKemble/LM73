#LM73 Temperature Sensor Library

<a href="http://www.ti.com/product/lm73">TI LM73</a> Temperature sensor IC library for Arduino and (TODO) AVR microcontrollers.


##Installing
###Arduino
Copy the arduino/LM73/ folder to your Arduino libraries folder.

If you are using Arduino 1.5 then you will need to move the .cpp and .h files into the src folder.

Add

    #include <LM73.h>
	#include <Wire.h>

to the top of the sketches that use the library.

###AVR (TODO)
Copy the LM73 folder to your project and add

    #include "LM73/LM73.h"

to the source files that use the library.

Examples in the examples folder.

--------

Zak Kemble

contact@zakkemble.co.uk
