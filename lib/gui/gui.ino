/**
 * @file gui.ino
 * @brief GUI Library DEV project
 * @version 1.0.0
 * @date 2022-07-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Definitions.h"
#include "GUI.h"

void setup() {
  // Initialize Serial
  Serial.begin( 9600 );

  // Initialize GUI
  gui_setup();
}

void loop() {
  // Draw GUI
  gui_draw( );

  delay( 500 );
}
