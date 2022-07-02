#include "CommunicationHandler.cpp";


void testCallback ( ) {
  Serial.println("Callback was called");
}

CommunicationHandler comm = CommunicationHandler( );

void setup() {
  // put your setup code here, to run once:
  comm.initialize();
}

void loop() {
  // put your main code here, to run repeatedly:

}
