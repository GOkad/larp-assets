/**
 * @file network_node.ino
 * @brief Network Node DEV project
 * @date 2022-07-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Definitions.h"

#define DEVICE_TYPE   NETWORK_NODE

#include "Communication.h"
#include "WiFiConnection.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Communication Node v.1.0");

  if ( !initializeESPNOW( ) ) {
    Serial.println("ESP NOW Failed to initialize");
  } else {
    getMacAddress( );
  }

}

void loop() {
  
  bool sender = false;
  // put your main code here, to run repeatedly:
  if ( sender ) {
    // TODO: Test sender - receiver [PING - AUTH]
    // TODO: Check how to broadcast without a specific mac address
    sendData( noPinsMini, PING, "" );
  }

  delay(5000);  
}
