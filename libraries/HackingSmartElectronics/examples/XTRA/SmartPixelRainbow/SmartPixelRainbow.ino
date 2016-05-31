////////////////////////////////////////////
//  
//  Trinket Sketch: Display rainbow on NeoPixel LED
//                  Uses the bobablox library to simplify code
//                  Uses Adafruit NeoPixel Library to drive NewPixel LED
//
////////////////////////////////////////////

// Include libraries
#include <Adafruit_NeoPixel.h>
#include <BobaBlox.h>

// Declare the NeoPixel LED (1 LED, pin #2, Pixel Type -- don't change)
// This can work for more than a single pixel in a "strip"
Adafruit_NeoPixel LEDStrip(1, 2, NEO_GRB + NEO_KHZ800);

// Run these statements one time
void setup() {
  
  // Initialize the LEDStrip (begin). Then, Show the strip to turn all pixels off
  LEDStrip.begin();
  LEDStrip.show();

}

void loop() {

  // Cycle through the rainbow, and repeat (helper function is in other tab)
  rainbowCycle(20);
}

