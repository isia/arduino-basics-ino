////////////////////////////////////////////
//  
//  Trinket: Random tones running Trinket at 16MHz
//
//  NOTE: Make sure to change your "board" in the Tools menu
//  to identify the Trinket as 16MHz
//
////////////////////////////////////////////

#include <BobaBlox.h>

// This include is required for 16MHz operation
#include <avr/power.h>
 
Speaker piezo(0);
unsigned int freq;

void setup() {
  
  // This line is required in Setup for the Trinket to
  // operate correctly at 16MHz
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  
}

void loop() {

  // Calculate a random frequency, 0-2500 in steps of 50
  freq = (random(50) * 50) + 50;

  // Beep the speaker and delay between notes
  piezo.beep (freq, 100);
  delay (10);
  
}