////////////////////////////////////////////
//  
//  Trinket: Blink the on-board LED (pin 1)
//  Turns LED on, then off. Repeat.
//
////////////////////////////////////////////

// Setup runs once at the beginning
void setup() {                

  // Initialize pin #1 for digital OUTPUT
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
}

// Loop repeats forever
void loop() {
  digitalWrite(1, HIGH);     // turn the LED on
  delay(50);                // wait for 1/2 second
  digitalWrite(1, LOW);      // turn the LED off
  delay(950);                // wait for 1/2 second
}
