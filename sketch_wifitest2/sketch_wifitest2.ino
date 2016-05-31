#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 6); // RX, TX
void setup()
 {
   pinMode(13, OUTPUT);
 // Open serial communications and wait for port to open:
 Serial.begin(9600);//9600
 mySerial.begin(9600);
 delay(5000);
// 
 long baud[] = { 9600, 19200, 38400, 74880, 115200 };
 int i = 7;
// for (i = 0; i < 5; i = i + 1) {
//  Serial.println(baud[i]);
//  mySerial.begin(baud[i]);
//  mySerial.println("AT+CIOBAUD=9600");
//  mySerial.println("AT+CIOBAUD=9600");
//  mySerial.println("AT+CIOBAUD=9600");
//  mySerial.println("AT+CIOBAUD=9600");
//  mySerial.println("AT+CIOBAUD=9600");
//  delay(1000);
// }

for (; i < 5; i = i + 1) {
  //Serial.println(baud[i]);
  Serial.begin(baud[i]);
  Serial.println("AT");
  Serial.println("AT");
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);  
  delay(5000);
 
  if(Serial.find("OK")){
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);              // wait for a second
    digitalWrite(13, LOW);
    delay(500);
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);              // wait for a second
    digitalWrite(13, LOW);  
    Serial.println("AT+CIOBAUD=9600");
    Serial.begin(9600);
    //Serial.println("OKOKOK");
    return;
  }
}
 //mySerial.begin(9600);
 
 //mySerial.println("AT+CIOBAUD=9600");
 //mySerial.begin(115200);
 Serial.println("Gogogo");
 }
void loop() // run over and ove
 {
 if (mySerial.overflow()) {
   Serial.println("SoftwareSerial overflow!");   
 }
 while (mySerial.available()>0 ) {
   Serial.write(mySerial.read());
   //delay(10);
 }
 while (Serial.available()>0 ){  
  mySerial.write(Serial.read());
//Serial.write(Serial.read());
  //delay(100);
  }
}
