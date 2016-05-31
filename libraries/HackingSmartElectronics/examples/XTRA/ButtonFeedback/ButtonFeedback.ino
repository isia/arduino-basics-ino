////////////////////////////////////////////
//  
//  Trinket: Beeps each time a button is released
//
////////////////////////////////////////////

#include <BobaBlox.h>

// Declarations
Button pushButton(2);    // Button is connected to Trinket pin #2
Speaker piezo(0);        // Speaker is connected to Trinket pin #0

// Setup runs once
void setup() {                

}

// Loop repeats forever
void loop() {
  
  // Each time a the button is released, sound the speaker
  if (pushButton.wasReleased()) {
	  piezo.beep(1000, 300);
  };
  
}
