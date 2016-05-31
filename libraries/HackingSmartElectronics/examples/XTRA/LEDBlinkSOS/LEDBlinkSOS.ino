////////////////////////////////////////////
//  
//  Trinket: Blink an LED. Uses BobaBlox library
//  Blinks "SO" in morse code. Repeat.
//
////////////////////////////////////////////

// Include the BobaBlox library
#include <BobaBlox.h>

// Declarations
LED boardLED(1);                  // Board LED on pin #1

// Setup runs once at the beginning
void setup() {                

}

// the loop routine runs over and over again forever:
void loop() {
  
  // Use the "blink" method to blink the LED declared as boardLED
  boardLED.blink(3);
  boardLED.blink(3, 1000);
  
}
