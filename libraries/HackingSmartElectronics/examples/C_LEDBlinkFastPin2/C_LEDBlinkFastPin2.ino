////////////////////////////////////////////
//  
//  Trinket: Fast Blink using Pin #2
//  Turns on an LED on, then off. Repeat.
//
////////////////////////////////////////////

// Setup runs once
void setup() {                

  // Initialize pin #2 for digital OUTPUT
  pinMode(2, OUTPUT);     

}

// Loop repeats forever
void loop() {
  digitalWrite(2, HIGH);     // turn the LED on
  delay(250);                // wait for a second
  digitalWrite(2, LOW);      // turn the LED off
  delay(250);                // wait for a second
}
