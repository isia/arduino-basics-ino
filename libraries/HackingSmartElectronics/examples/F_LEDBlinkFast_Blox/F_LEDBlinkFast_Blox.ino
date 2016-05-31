////////////////////////////////////////////
//  
//  Trinket: Blink an LED. Uses BobaBlox library
//  Turns on an LED on, then off. Repeat.
//
////////////////////////////////////////////

// Include the library
#include <BobaBlox.h>

// Declarations
LED boardLED(1);    // Declare an LED on pin #1

// Setup runs once at the beginning
void setup() {
}

// Loop repeats forever. Use boardLED's "blink" method
void loop() {
  boardLED.blink(1, 100);
}
