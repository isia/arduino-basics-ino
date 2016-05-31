////////////////////////////////////////////
//  
//  Trinket: Use switch to turn on/off LED.
//           Uses BobaBlox library
//
////////////////////////////////////////////

// Include libraries
#include <BobaBlox.h>

// Declarations
LED boardLED(1);        // Declare an LED on pin #1
Button pushButton(2);   // Button is connected to pin #2

// Setup runs once at the beginning
void setup() {                

}

// Loop repeats forever
void loop() {
  
  // Check the button. Set LED on/off according to button state
  if (pushButton.isDown()) {
	boardLED.on();
  } else {
  	boardLED.off();
  }
  
}
