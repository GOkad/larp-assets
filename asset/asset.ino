#include "Asset.cpp"

Asset asset = Asset( USER_DEVICE );

void setup() {
  Serial.begin( 4800 );
  // put your setup code here, to run once:
  if ( asset.initialize( ) ) {
    Serial.println("Asset was initialized");
  } else {
    // TODO: Add LED handler
    Serial.println("Something went wrong");
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
