/****************************************************************************************************************************************************
 *  TITLE: ESP-NOW Getting Started Examples
 *
 *  By Frenoy Osburn
 *  YouTube Video: https://youtu.be/_cNAsTB5JpM
 ****************************************************************************************************************************************************/

 /********************************************************************************************************************
  * Please make sure that you install the board support package for the ESP8266 boards.
  * You will need to add the following URL to your Arduino preferences.
  * Boards Manager URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
 ********************************************************************************************************************/
 
 /********************************************************************************************************************
 *  Board Settings:
 *  Board: "WeMos D1 R1 or Mini"
 *  Upload Speed: "921600"
 *  CPU Frequency: "80MHz"
 *  Flash Size: "4MB (FS:@MB OTA:~1019KB)"
 *  Debug Port: "Disabled"
 *  Debug Level: "None"
 *  VTables: "Flash"
 *  IwIP Variant: "v2 Lower Memory"
 *  Exception: "Legacy (new can return nullptr)"
 *  Erase Flash: "Only Sketch"
 *  SSL Support: "All SSL ciphers (most compatible)"
 *  COM Port: Depends *On Your System*
 *********************************************************************************************************************/
// ESP NOW
#include<ESP8266WiFi.h>
#include<espnow.h>
#include "dataPacket.h"
// TFT Display
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#define MY_NAME   "SLAVE_NODE"
int timer = 0;
const int loopDelayTimeout = 2000;


// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;

// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     D1
#define TFT_RST    D0  // you can also connect this to the Arduino reset in which case, set this #define pin to -1!
#define TFT_DC     D2

// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)

// For 1.44" and 1.8" TFT with ST7735 use
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
float p = 3.1415926;

String displayMessage = "Gosha... KAR";
String lastMessage = "";
String boardID = "ESP 07";
bool redrawScreen = false;

prop dangerProp = { "", 0, false };
prop packageProp = { "", 0, false };
prop lootboxProp = { "", 0, false };

#include "Display.h"
 
void setup() {
  
  Serial.begin(115200);     // initialize serial port


  // ESP Now
  // Serial.println();
  // Serial.println();
  // Serial.println();
  // Serial.print("Initializing...");
  // Serial.println(MY_NAME);
  // Serial.print("My MAC address is: ");
  // Serial.println(WiFi.macAddress());

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();        // we do not want to connect to a WiFi network

  if(esp_now_init() != 0) {
    Serial.println("ESP-NOW initialization failed");
    return;
  }

  esp_now_register_recv_cb(dataReceived);   // this function will get called once all data is sent

  Serial.println("Initialized.");

  // TFT Display
  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;
  // drawGUI( );
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0,0);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextWrap(true);
  tft.setTextSize(1);
  tft.println("Are da pushim koz?");
  tft.println("        W          ");
  tft.println("       WWW         ");
  tft.println("       WWW         ");
  tft.println("      WWWWW        ");
  tft.println("W     WWWWW     W  ");
  tft.println("WWW   WWWWW   WWW  ");
  tft.println(" WWW  WWWWW  WWW   ");
  tft.println("  WWW  WWW  WWW    ");
  tft.println("   WWW WWW WWW     ");
  tft.println("     WWWWWWW       ");
  tft.println("  WWWW  |  WWWW    ");
  tft.println("        |          ");
  tft.println("        |");
  delay(500);

}

void loop() {
  
  return;

  // Serial.println("----");
  // Serial.print("Danger : ");
  // Serial.print( dangerProp.macAddress );
  // Serial.print(" | Last ping : ");
  // Serial.print( dangerProp.lastPing );
  // Serial.println(" | DIFF : "+String( millis() - dangerProp.lastPing ));
  // Serial.print("Package : ");
  // Serial.print( packageProp.macAddress );
  // Serial.print(" | Last ping : ");
  // Serial.print( packageProp.lastPing );
  // Serial.println(" | DIFF : "+String(  ));

  // Serial.println("------Loop-----");
  // Serial.print("Last Ping : ");
  // Serial.print(dangerProp.lastPing);
  // Serial.print(" | ");
  // Serial.print("Current time : ");
  // Serial.print( millis() );
  // Serial.print(" | ");
  // Serial.print("Diff: ");
  // Serial.println( millis() - dangerProp.lastPing );

  if ( (millis() - packageProp.lastPing) > 50000 ) {
    packageProp.isActive = false;
    Serial.println( packageProp.isActive );
    redrawScreen = true;
  }
  
  if ( (millis() - dangerProp.lastPing) > 50000 ) {
    dangerProp.isActive = false;
    Serial.println( dangerProp.isActive );
    redrawScreen = true;
  }

  if ( redrawScreen ) {
    // drawGUI( );
  }

  loopAnimations( );
  

  delay(loopDelayTimeout);
}

// Handle recieved data
void dataReceived(uint8_t *senderMac, uint8_t *data, uint8_t dataLength) {
  char macStr[18];
  dataPacket packet;  

  memcpy(&packet, data, sizeof(packet));
  
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", senderMac[0], senderMac[1], senderMac[2], senderMac[3], senderMac[4], senderMac[5]);

  if ( packet.type == DANGER ) {
    // Serial.println("------Update-----");
    // Serial.print("Last Ping : ");
    // Serial.print(dangerProp.lastPing);
    // Serial.print(" | ");
    // Serial.print("Current time : ");
    // Serial.print( millis() );
    // Serial.print(" | ");
    // Serial.print("Diff: ");
    // Serial.println( millis() - dangerProp.lastPing );
    dangerProp.macAddress = String(macStr);
    dangerProp.lastPing = millis( );
    dangerProp.isActive = true;
    
  }

  if ( packet.type == PROP ) {
    packageProp.macAddress = String(macStr);
    packageProp.lastPing = millis( );
    packageProp.isActive = true;
  }
  
  // Serial.println("-----");
  // Serial.println(boardID);
  // Serial.print("Received data from: ");
  // Serial.println(macStr);
  // Serial.print("Timer[Distance]: ");
  // Serial.println(timer);
  // Serial.print("Type: ");
  // Serial.println(DATA_TYPES[packet.type]);
  // Serial.print("Active distance: ");
  // Serial.println(packet.activeDistance);
  // Serial.print("Threat level: ");
  // Serial.println(packet.threatLevel);

  redrawScreen = true;
  timer = 0;
}

// Display methods
void drawGUI ( ) {
  Serial.println("Redraw GUI");

  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0,0);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextWrap(true);
  tft.setTextSize(1);

  tft.println("From Krasi i Goki :");
  tft.println("WDesign Presents : ");
  tft.println("-------------------");

  // Print Prop
  tft.println("*******************");
  if ( packageProp.isActive ) {
    tft.println(DATA_TYPES[PROP]);
    tft.println("MAC Address: ");
    tft.println(packageProp.macAddress);
    tft.print("Last Ping: ");
    tft.println(packageProp.lastPing);
    tft.print("DIFF: ");
    tft.println(millis() - packageProp.lastPing);
  } else {
    tft.println("Scanning...");
  }
  tft.println("*******************");
  
  // Print Danger
  Serial.print("Danger: ");
  Serial.println( dangerProp.isActive );
  if ( dangerProp.isActive ) {
    tft.setTextColor(ST77XX_RED);
    tft.println("*******************");
    tft.setTextColor(ST77XX_YELLOW);
    tft.println(DATA_TYPES[DANGER]);
    tft.println("MAC Address: ");
    tft.println(dangerProp.macAddress);
    tft.print("Last Ping: ");
    tft.println(dangerProp.lastPing);
    tft.print("DIFF: ");
    tft.println(millis() - dangerProp.lastPing);
    tft.setTextColor(ST77XX_RED);
    tft.println("*******************");
  }
  



  redrawScreen = false;
}

void loopAnimations ( ) {
  int animationDelay = 2000;
  // large block of text
  tft.fillScreen(ST77XX_BLACK);
  drawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ");
  delay(animationDelay);

  // tft print function!
  tftPrintTest();
  delay(animationDelay);

  // a single pixel
  tft.drawPixel(tft.width()/2, tft.height()/2, ST77XX_GREEN);
  delay(animationDelay);

  // line draw test
  testlines(ST77XX_YELLOW);
  delay(animationDelay);

  // optimized lines
  testfastlines(ST77XX_RED, ST77XX_BLUE);
  delay(animationDelay);

  testdrawrects(ST77XX_GREEN);
  delay(animationDelay);

  testfillrects(ST77XX_YELLOW, ST77XX_MAGENTA);
  delay(animationDelay);

  tft.fillScreen(ST77XX_BLACK);
  testfillcircles(10, ST77XX_BLUE);
  testdrawcircles(10, ST77XX_WHITE);
  delay(animationDelay);

  testroundrects();
  delay(animationDelay);

  testtriangles();
  delay(animationDelay);

  mediabuttons();
  delay(animationDelay);
}
 
void testlines(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, 0, x, tft.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, 0, tft.width()-1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, 0, x, tft.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, 0, 0, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, tft.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, tft.height()-1, tft.width()-1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, 0, y, color);
    delay(0);
  }
}

void drawtext(String text ) {
  // uint16_t color
  tft.setCursor(10,0);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextWrap(true);
  tft.setTextSize(1);
  tft.println(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  tft.fillScreen(ST77XX_BLACK);
  int color = 0xF800;
  int t;
  int w = tft.width()/2;
  int x = tft.height()-1;
  int y = 0;
  int z = tft.width();
  for(t = 0 ; t <= 15; t++) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void testroundrects() {
  tft.fillScreen(ST77XX_BLACK);
  int color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = tft.width()-2;
    int h = tft.height()-2;
    for(i = 0 ; i <= 16; i+=1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}

void tftPrintTest() {
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);
  delay(1500);
  tft.setCursor(0, 0);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(0);
  tft.println("Hello World!");
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_GREEN);
  tft.print(p, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(ST77XX_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(" seconds.");
}

void mediabuttons() {
  // play
  tft.fillScreen(ST77XX_BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, ST77XX_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ST77XX_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_GREEN);
}