#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

const int D3 = 0;
const int D4 = 2;
bool increase = true;
int dutyCycle = 124;
int movementDelay = 1000;

const char index_html[] PROGMEM = R"rawliteral()rawliteral";

void setup(void){
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  // Soft access point
  WiFi.softAP("PWM_Wireless", "");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/", HTTP_GET, handleRoot);     // Call the 'handleRoot' function when a client requests URI "/"
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"
  server.on("/api/pwm", HTTP_POST, handlePWM);
  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}

void loop(void){
  // Listen for HTTP requests from clients
  server.handleClient();
}

void handleRoot() {                         // When URI / is requested, send a web page with a button to toggle the LED
  server.send(200, "text/html", index_html);
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}
void handlePWM ( ) {

}

