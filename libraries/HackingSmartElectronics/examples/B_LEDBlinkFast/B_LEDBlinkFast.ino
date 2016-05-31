////////////////////////////////////////////
//  
//  Trinket: Blink on-board LED. Faster.
//  Turns on an LED on, then off. Repeat.
//
////////////////////////////////////////////

// Setup runs once
void setup() {                

  // Initialize pin #1 for digital OUTPUT
  pinMode(1, OUTPUT);     

}

// Loop repeats forever
void loop() {
  digitalWrite(1, HIGH);     // turn the LED on
  delay(250);                // wait for half a second
  digitalWrite(1, LOW);      // turn the LED off
  delay(250);                // wait for half a second
}
