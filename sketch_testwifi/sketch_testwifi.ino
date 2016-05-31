#include <SoftwareSerial.h>
SoftwareSerial wifiSerial(7, 6); // RX, TX
#define SSID "Zeo"
#define PASS "ilovezeo"

#define IP "10.55.26.95"
#define PORT "3223"
boolean wifion = false;
int i;
void setup()
{
 // Open serial communications and wait for port to open:
 Serial.begin(9600);//9600
 wifiSerial.begin(9600);
 Serial.write("Hello world");
 pinMode(13, OUTPUT);
 
 
}

void loop(){
  if(wifion) {
    Serial.println("Writing to socket");
    updateTemp("test");
  } else {
    wifiSerial.println("AT");
    delay(5000);
    if(wifiSerial.find("OK")){
      Serial.println("RECEIVED: OK, connecting to WIFI");
      wifion = connectWiFi();
    }
    delay(10000);
  }  
}

void updateTemp(String tenmpF){
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",";
  cmd += PORT;
  wifiSerial.println(cmd);
  delay(2000);
  if(wifiSerial.find("Error")){
    return;
  }
  cmd = "UPDATE:";
  cmd += tenmpF;
  cmd += "\r\n";
  wifiSerial.print("AT+CIPSEND=");
  wifiSerial.println(cmd.length());
  if(wifiSerial.find(">")){
    wifiSerial.print(cmd);
  }else{
    wifiSerial.println("AT+CIPCLOSE");
  }
}

 
boolean connectWiFi(){
  wifiSerial.println("AT+CWMODE=1");
  delay(2000);
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  wifiSerial.println(cmd);
  delay(5000);
  if(wifiSerial.find("OK")){
    Serial.println("Connected to WIFI");
    return true;
  }else{
    Serial.println("Nfail to connect to WIFI");
    return false;
  }
}
