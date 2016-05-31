////////////////////////////////////////////
//  
//  Trinket: Blink an LED. A VARIABLE holds the LED pin number
//  Turns on an LED on, then off. Repeat.
//
////////////////////////////////////////////

// Declarations
int pinLED = 2;                  // Set this variable to the pin number

// Setup runs once at the beginning
void setup() {                

  // Initialize pin in variable pinLED for digital OUTPUT
  pinMode(pinLED, OUTPUT);     

}

// Loop repeats forever
void loop() {
  digitalWrite(pinLED, HIGH);    // turn the LED on
  delay(1000);                   // wait for a second
  digitalWrite(pinLED, LOW);     // turn the LED off
  delay(1000);                   // wait for a second
}
