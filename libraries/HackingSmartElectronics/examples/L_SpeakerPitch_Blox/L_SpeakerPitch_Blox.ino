////////////////////////////////////////////
//  
//  Trinket: Beeps with increasing frequency
//
////////////////////////////////////////////

// Include libraries
#include <BobaBlox.h>

// Declarations
Speaker piezo(2);       // Declare a speaker using pin #2
int freq;		// Variable freq holds the frequency

// Setup runs once
void setup() {                
}

// Loop repeats forever
void loop() {
  
  // Loop freq from 50 to 6000 in steps of 50
  for (freq=50; freq<6000; freq=freq+50) {
    piezo.beep(freq, 200);
    delay (100);
  }
  
}
