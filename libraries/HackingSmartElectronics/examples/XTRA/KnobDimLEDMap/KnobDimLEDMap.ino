////////////////////////////////////////////
//  
//  Trinket: Use knob to dim an LED.
//           Uses BobaBlox library
//
////////////////////////////////////////////

// Include libraries
#include <BobaBlox.h>

// Declarations
LED boardLED(1);        // Declare an LED on pin #1
Knob bluKnob(1);        // Knob is connected to Analog pin #1 (digital pin #2)

int knobValue;          // This holds the knob value
int LEDBrightness;		// This holds LED brightness (0-255)
// the setup routine runs once at the beginning
void setup() {                

}

// The loop routine runs over and over again forever:
void loop() {
  
  // Check the knob value
  // Convert the knob value (0-1023) to a brightness (0-255).
  // Note: see the Map command in the reference
  knobValue = bluKnob.value();
  LEDBrightness = map(knobValue, 0, 1023, 0, 255);
  boardLED.setBrightness(LEDBrightness);
  
}
