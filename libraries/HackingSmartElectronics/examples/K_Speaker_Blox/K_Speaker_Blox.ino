////////////////////////////////////////////
//  
//  Trinket: Beeps a speaker
//
////////////////////////////////////////////

// Include libraries
#include <BobaBlox.h>

// Declarations
Speaker piezo(2);       	// Declare a speaker using pin #2

// Setup runs once
void setup() {                
}

// Loop repeats forever
void loop() {
  
    piezo.beep(1000, 200);	// Beep the speaker at 1000 Hz, for 200 millis
    delay (100);
  
}
