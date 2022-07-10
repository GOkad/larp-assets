/**
 * @file network_node.ino
 * @brief Network Node DEV project
 * @date 2022-07-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Definitions.h"

// Define the type of this device
#define DEVICE_TYPE   NETWORK_NODE

// TODO: Add SSID Definition based on device/MAC
#define SSID          "NetNode_1"
#define PASSWORD      ""

#include "Communication.h"
#include "RequestResponseHandlers.h"
#include "WiFiConnection.h"

unsigned long lastSend = 0;

void setup() {
  // put your setup code here, to run once:
  // Serial.begin(115200);
  Serial.begin(9600);
  Serial.println("Communication Node v.1.0");

  if ( !initializeESPNOW( ) ) {
    Serial.println("ESP NOW Failed to initialize");
  } else {
    getMacAddress( );
  }

  if ( !initializeWiFi(SSID, PASSWORD) ) {
    Serial.println("WiFi server failed to initialize");
  } else {
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());
  }

}

void loop() {
  // put your main code here, to run repeatedly:

  bool sender = true;
  
  if (
    sender &&
    ( (millis() - lastSend) >= 5000 )
  ) {
    // TODO: Test sender - receiver [PING - AUTH]
    // TODO: Check how to broadcast without a specific mac address
    sendData( esp32dev, PING, "esp 8266" );
    lastSend = millis( );
  }

  // Listen for HTTP requests from clients
  server.handleClient();

}
