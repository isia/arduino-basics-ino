#include <SoftwareSerial.h>
SoftwareSerial RFID(2, 3); // RX and TX
 
int i;
 
void setup()
{
  RFID.begin(9600);    // start serial to RFID reader
  Serial.begin(9600);  // start serial to PC 
}
 
int readVal = 0; // individual character read from serial
unsigned int readData[10]; // data read from serial
int counter = -1; // counter to keep position in the buffer
char tagId[11]; // final tag ID converted to a string 
 
void parseTag() {
  int i;
  for (i = 0; i < 10; ++i) {
    tagId[i] = readData[i];
  }
  tagId[10] = 0;
}

void printTag() {
  Serial.print("Tag value: ");
  Serial.println(tagId);
}

 
void loop()
{
  if (RFID.available() > 0) {
		// read the incoming byte:
		readVal = RFID.read();
		
		// a "2" signals the beginning of a tag
		if (readVal == 2) {
			counter = 0; // start reading
		} 
		// a "3" signals the end of a tag
		else if (readVal == 3) {
			// process the tag we just read
			parseTag();
			printTag();
			// clear serial to prevent multiple reads
			//clearSerial();
			
			// reset reading state
			counter = -1;
		}
		// if we are in the middle of reading a tag
		else if (counter >= 0) {
			// save valuee
			readData[counter] = readVal;
			
			// increment counter
			++counter;
		} 
	}
}
