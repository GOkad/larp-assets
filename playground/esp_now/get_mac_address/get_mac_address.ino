#include <ESP8266WiFi.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);

  Serial.println("---");
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());

  WiFi.softAP("ESP", "");
  Serial.print("IP address for network ");
  Serial.print("ESP");
  Serial.print(" : ");
  Serial.println(WiFi.softAPIP());
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
