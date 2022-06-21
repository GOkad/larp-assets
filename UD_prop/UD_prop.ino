/**
 * @file UD_prop.ino
 * @author George Okadarov
 * @brief [WIP] User device asset
 * @version 1.2.0
 * @date 2022-06-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Definitions.h"
#include "_communication.h"
#include "_gui.h"


// TODO: Add GUI TFT Screen
// TODO: Add GPS Tracking and handling
// TODO: Add I/O Expander and screens
// TODO: Add LED error handler


void setup() {
  // Begin serial communication
  Serial.begin(115200);

  // Setup ESP-NOW
  comm_setup( );
  gui_setup();


}

void loop() {
  // put your main code here, to run repeatedly:

  gui_draw();

}
