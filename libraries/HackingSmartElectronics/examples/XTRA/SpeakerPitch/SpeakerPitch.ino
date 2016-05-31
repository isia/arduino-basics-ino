////////////////////////////////////////////
//  
//  Trinket: Beeps with increasing frequency
//
//	NOTE: Each half step musically changes frequency
//  by the 12th root of 2
//
////////////////////////////////////////////

// Include libraries
#include <BobaBlox.h>

// Declarations
Speaker piezo(0);       // Declare a speaker using pin #
int freq;

// the setup routine runs once at the beginning
void setup() {                

}

// The loop routine runs over and over again forever:
void loop() {
  
  // Declare a variable called "freq" to hold the frequency
  int freq;
  
  // Loop freq from 50 to 6000 in musical half-steps
  // (Increase each step by 12th root of 2)
  for (freq=50; freq<6000; freq=freq * 1.0595) {
    piezo.beep(freq, 200);
    delay (100);
  }
  
}