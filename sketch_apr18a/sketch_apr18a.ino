#include <ESP8266WiFi.h>

const char* ssid = "Zeo";
const char* password = "ilovezeo";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  server.begin();
  Serial.print("IP-адрес нашего модуля: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  client.flush();
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nhello from esp8266!\n";
  client.print(s);
  delay(1);
}
