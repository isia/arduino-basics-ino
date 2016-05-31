////////////////////////////////////////////
//  
//  Trinket: Use knob to affect an LED blink rate.
//
////////////////////////////////////////////

// Include libraries
#include <BobaBlox.h>

// Declarations
LED boardLED(1);        // Declare an LED on pin #1
Knob bluKnob(1);        // Knob is connected to Analog pin #1 (Trinket pin #2)

int knobValue;          // This will hold the knob value
int blinkDelay;			// This will hold the blink delay

// the setup routine runs once at the beginning
void setup() {                

}

// The loop routine runs over and over again forever:
void loop() {
  
  // Check the knob value
  // Convert the knob (0-1023) to a 0-1 second delay (0-1000).
  // Note: see the Map command reference
  knobValue = bluKnob.value();
  blinkDelay = map(knobValue, 0, 1023, 0, 1000);
  boardLED.blink(1, blinkDelay);
  
}
