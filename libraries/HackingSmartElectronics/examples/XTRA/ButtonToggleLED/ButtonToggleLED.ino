////////////////////////////////////////////
//  
//  Trinket: Use switch to turn on/off LED.
//           Uses BobaBlox library
//           Turns off an LED on when switch
//           is pressed. On otherwise.
//
////////////////////////////////////////////

// Include libraries
#include <BobaBlox.h>

// Declarations
LED boardLED(1);        // Declare an LED on pin #1
Button pushButton(2);   // Switch is connected to pin #2

int LEDState = 0;   // LED State = 0 for off. LED State = 1 for on.

// Setup runs once at the beginning
void setup() {                

}

// Loop repeats forever
void loop() {
  
  // Check the button. Set LED on/off according to button state
  if (pushButton.wasPressed()) {

    LEDState = 1 - LEDState;
    if (LEDState == 1) {
    boardLED.on();
    } else {
      boardLED.off();
    }

  }
 
}