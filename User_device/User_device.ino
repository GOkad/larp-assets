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
