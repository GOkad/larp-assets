const int D1 = 5;
const int D2 = 4;
const int D3 = 0;
const int D4 = 2;
bool increase = true;
int dutyCycle = 124;
int movementDelay = 1000;

void setup() {
  Serial.begin(115200);
  // pinMode(D1,OUTPUT);
  // pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);

  // digitalWrite(D1,HIGH);
  // digitalWrite(D2,HIGH);
  // digitalWrite(D3,HIGH);
  // digitalWrite(D4,HIGH);


}

void loop() {
  // increase the LED brightness

  Serial.print("dutyCycle: ");
  Serial.println( dutyCycle );

  if ( dutyCycle >= 255 ) {
    increase = false;
  } else if ( dutyCycle <= 125 ) {
    increase = true;
  }

  if ( increase ) { dutyCycle++; }
  else { dutyCycle--; }

  pwm(dutyCycle, true);
  delay(movementDelay);
  pwm(dutyCycle, false);
  delay(movementDelay);

  // analogWrite(D2,dutyCycle);

  // digitalWrite(D3,LOW);
  // digitalWrite(D4,HIGH);
  // delay(500);
  // digitalWrite(D3,HIGH);
  // digitalWrite(D4,LOW);
  // delay(500);

  delay( 10 );

  // digitalWrite(D1,!digitalRead(D1));
  // digitalWrite(D2,!digitalRead(D2));
  // digitalWrite(D3,!digitalRead(D3));
  // digitalWrite(D4,!digitalRead(D4));

  // delay( 500 );

}

void pwm ( int dutyCycle, bool defaultPol ) {

  analogWrite(D3,defaultPol ? 0 : dutyCycle);
  analogWrite(D4,defaultPol ? dutyCycle : 0);

}