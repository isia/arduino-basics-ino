////////////////////////////////////////////
//  
//  Trinket: Use a knob to change speaker frequency
//
////////////////////////////////////////////

// Include libraries
#include <BobaBlox.h>

// Declarations
Knob myKnob(1);       // Photocell is connected to Analog pin #1 (Trinket pin #2)
Speaker piezo(0);        // Speaker is connected to Trinket pin #0
int value;				 // To hold the value returned from the knob
int freq;                // The value converted to a frequency

// the setup routine runs once at the beginning
void setup() {                

}

// The loop routine runs over and over again forever:
void loop() {
  
  // Check the photocell value and convert the knob (0-1023) to a frequency
  value = myKnob.value();
  freq = map(value, 0, 1023, 0, 6000);

  // Use the frequency to play the speaker
  piezo.beep(freq, 100);
  delay(10);
  
}