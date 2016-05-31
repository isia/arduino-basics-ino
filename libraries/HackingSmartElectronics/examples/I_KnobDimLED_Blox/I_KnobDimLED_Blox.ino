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

// Setup runs once
void setup() {                

}

// Loop repeats forever
void loop() {
  
  // Get the knob value and use it to set the LED brightness
  knobValue = bluKnob.value();
  boardLED.setBrightness(knobValue);
  
}
