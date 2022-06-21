/**
 * @file UD_prop.ino
 * @author George Okadarov
 * @brief [WIP] User device asset
 * @version 1.1.0
 * @date 2022-06-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Definitions.h"
#include<ESP8266WiFi.h>
#include<espnow.h>
#include "_communication.h"


// TODO: Add GUI TFT Screen
// TODO: Add GPS Tracking and handling
// TODO: Add I/O Expander and screens
// TODO: Add LED error handler


void setup() {
  // Begin serial communication
  Serial.begin(115200);

  // Setup ESP-NOW
  comm_setup( );


}

void loop() {
  // put your main code here, to run repeatedly:

}
