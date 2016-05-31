////////////////////////////////////////////
//  
//  Trinket: Use knob to dim an LED, adjusting the range.
//           Uses BobaBlox library
//
////////////////////////////////////////////

// Include libraries
#include <BobaBlox.h>

// Declarations
LED boardLED(1);        // Declare an LED on pin #1
Knob bluKnob(1);        // Knob is connected to Analog pin #1 (digital pin #2)

int knobValue;          // Variable to hold the knob value

// Setup runs once
void setup() {                

}

// Loop repeats forever
void loop() {
  
  // Check the knob value (and, map to correct range, 0-255)
  knobValue = bluKnob.value(0, 255);
  boardLED.setBrightness(knobValue);
  
}
