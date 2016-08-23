#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266HTTPClient.h>
#include <nokiascreen.h>
#include <SimpleTimer.h>

// the timer object
SimpleTimer timer;



const char* ssid = "Zeo-Test";
const char* password = "CnjgNtktajysDctn";

const char* host = "dyndns.isia.zeo.lcl";
String url = "/ESP8266-b";
byte mac[6];

void setup() {
//    pinMode(LDR, INPUT);
//#    pinMode(BUTTON, INPUT);
//#    pinMode(RED, OUTPUT);
//#    pinMode(GREEN, OUTPUT);
//#    pinMode(BLUE, OUTPUT);

    LCDInit(); //Init the LCD
    LCDClear();
    gotoXY(0, 0);
    char charBuf[15];
    WiFi.macAddress(mac);//.toCharArray(charBuf, 15);
    sprintf(charBuf,"%02X%02X%02X%02X%02X%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[6]);
    LCDString(charBuf);
    delay(3000);


    Serial.begin(9600);
    warn("Booting");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        warn("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }

    // Port defaults to 8266
    // ArduinoOTA.setPort(8266);

    // Hostname defaults to esp8266-[ChipID]
    // ArduinoOTA.setHostname("myesp8266");

    // No authentication by default
    // ArduinoOTA.setPassword((const char *)"123");

    ArduinoOTA.onStart([]() {
        warn("OTA Start");
    });
    ArduinoOTA.onEnd([]() {
        warn("End");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        //char charBuf[15];
        //sprintf(charBuf, "Progress: %u%%\r", (progress / (total / 100)));
        //warn(charBuf);
    });
    ArduinoOTA.onError([](ota_error_t error) {
        warn("Error[]: ");
        if (error == OTA_AUTH_ERROR) warn("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) warn("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) warn("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) warn("Receive Failed");
        else if (error == OTA_END_ERROR) warn("End Failed");
    });
    ArduinoOTA.begin();
    Serial.println("Ready");
    warn("DOP was here!");
//warn(WiFi.localIP());
    Serial.print("Mac address: ");
    Serial.println(WiFi.macAddress());

    timer.setInterval(1000, repeatMe);
}

void loop() {
  ArduinoOTA.handle();
  delay(800);
}


// a function to be executed periodically
void repeatMe() {
    if(WiFi.waitForConnectResult() != WL_CONNECTED) {
        gotoXY(0, 0);
        LCDString("Connection lost");
        delay(5000);
        ESP.restart();
    }
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        return;
    }
    // This will send the request to the server
    client.print(String("PUT ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
}

void warn(char *characters) {
   gotoXY(0,3);
   LCDString(characters);
}

