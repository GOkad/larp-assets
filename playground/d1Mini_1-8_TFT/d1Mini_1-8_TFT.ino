/***************************************************
  This is a library for the Adafruit 1.8" SPI display.
This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
The 1.8" TFT shield
  ----> https://www.adafruit.com/product/802
The 1.44" TFT breakout
  ----> https://www.adafruit.com/product/2088
as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618
  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

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
Adafruit_ST7735 screen = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// For 1.54" TFT with ST7789
//Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS,  TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
//#define TFT_SCLK    // set these to be whatever pins you like!
//#define TFT_MOSI D1   // set these to be whatever pins you like!
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


float p = 3.1415926;

void setup(void) {
  Serial.begin(115200);
  Serial.print("Hello! ST77xx TFT Test");

  // Use this initializer if you're using a 1.8" TFT
  screen.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  // Use this initializer (uncomment) if you're using a 1.44" TFT
  // screen.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab

  // Use this initializer (uncomment) if you're using a 0.96" 180x60 TFT
  //screen.initR(INITR_MINI160x80);   // initialize a ST7735S chip, mini display

  // Use this initializer (uncomment) if you're using a 1.54" 240x240 TFT
//  screen.init(128, 128);   // initialize a ST7789 chip, 240x240 pixels

  Serial.println("Initialized");

  uint16_t time = millis();
  screen.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  // large block of text
  screen.fillScreen(ST77XX_BLACK);
  testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", ST77XX_WHITE);
  delay(1000);

  // tft print function!
  tftPrintTest();
  delay(4000);

  // a single pixel
  screen.drawPixel(screen.width()/2, screen.height()/2, ST77XX_GREEN);
  delay(500);

  // line draw test
  testlines(ST77XX_YELLOW);
  delay(500);

  // optimized lines
  testfastlines(ST77XX_RED, ST77XX_BLUE);
  delay(500);

  testdrawrects(ST77XX_GREEN);
  delay(500);

  testfillrects(ST77XX_YELLOW, ST77XX_MAGENTA);
  delay(500);

  screen.fillScreen(ST77XX_BLACK);
  testfillcircles(10, ST77XX_BLUE);
  testdrawcircles(10, ST77XX_WHITE);
  delay(500);

  testroundrects();
  delay(500);

  testtriangles();
  delay(500);

  mediabuttons();
  delay(500);

  Serial.println("done");
  delay(1000);
}

void loop() {
  screen.invertDisplay(true);
  delay(500);
  screen.invertDisplay(false);
  delay(500);
}
void testlines(uint16_t color) {
  screen.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < screen.width(); x+=6) {
    screen.drawLine(0, 0, x, screen.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < screen.height(); y+=6) {
    screen.drawLine(0, 0, screen.width()-1, y, color);
    delay(0);
  }

  screen.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < screen.width(); x+=6) {
    screen.drawLine(screen.width()-1, 0, x, screen.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < screen.height(); y+=6) {
    screen.drawLine(screen.width()-1, 0, 0, y, color);
    delay(0);
  }

  screen.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < screen.width(); x+=6) {
    screen.drawLine(0, screen.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < screen.height(); y+=6) {
    screen.drawLine(0, screen.height()-1, screen.width()-1, y, color);
    delay(0);
  }

  screen.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < screen.width(); x+=6) {
    screen.drawLine(screen.width()-1, screen.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < screen.height(); y+=6) {
    screen.drawLine(screen.width()-1, screen.height()-1, 0, y, color);
    delay(0);
  }
}

void testdrawtext(char *text, uint16_t color) {
  screen.setCursor(0, 0);
  screen.setTextColor(color);
  screen.setTextWrap(true);
  screen.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
  screen.fillScreen(ST77XX_BLACK);
  for (int16_t y=0; y < screen.height(); y+=5) {
    screen.drawFastHLine(0, y, screen.width(), color1);
  }
  for (int16_t x=0; x < screen.width(); x+=5) {
    screen.drawFastVLine(x, 0, screen.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  screen.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < screen.width(); x+=6) {
    screen.drawRect(screen.width()/2 -x/2, screen.height()/2 -x/2 , x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  screen.fillScreen(ST77XX_BLACK);
  for (int16_t x=screen.width()-1; x > 6; x-=6) {
    screen.fillRect(screen.width()/2 -x/2, screen.height()/2 -x/2 , x, x, color1);
    screen.drawRect(screen.width()/2 -x/2, screen.height()/2 -x/2 , x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < screen.width(); x+=radius*2) {
    for (int16_t y=radius; y < screen.height(); y+=radius*2) {
      screen.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < screen.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < screen.height()+radius; y+=radius*2) {
      screen.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  screen.fillScreen(ST77XX_BLACK);
  int color = 0xF800;
  int t;
  int w = screen.width()/2;
  int x = screen.height()-1;
  int y = 0;
  int z = screen.width();
  for(t = 0 ; t <= 15; t++) {
    screen.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void testroundrects() {
  screen.fillScreen(ST77XX_BLACK);
  int color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = screen.width()-2;
    int h = screen.height()-2;
    for(i = 0 ; i <= 16; i+=1) {
      screen.drawRoundRect(x, y, w, h, 5, color);
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
  screen.setTextWrap(false);
  screen.fillScreen(ST77XX_BLACK);
  screen.setCursor(0, 30);
  screen.setTextColor(ST77XX_RED);
  screen.setTextSize(1);
  screen.println("Hello World!");
  screen.setTextColor(ST77XX_YELLOW);
  screen.setTextSize(2);
  screen.println("Hello World!");
  screen.setTextColor(ST77XX_GREEN);
  screen.setTextSize(3);
  screen.println("Hello World!");
  screen.setTextColor(ST77XX_BLUE);
  screen.setTextSize(4);
  screen.print(1234.567);
  delay(1500);
  screen.setCursor(0, 0);
  screen.fillScreen(ST77XX_BLACK);
  screen.setTextColor(ST77XX_WHITE);
  screen.setTextSize(0);
  screen.println("Hello World!");
  screen.setTextSize(1);
  screen.setTextColor(ST77XX_GREEN);
  screen.print(p, 6);
  screen.println(" Want pi?");
  screen.println(" ");
  screen.print(8675309, HEX); // print 8,675,309 out in HEX!
  screen.println(" Print HEX!");
  screen.println(" ");
  screen.setTextColor(ST77XX_WHITE);
  screen.println("Sketch has been");
  screen.println("running for: ");
  screen.setTextColor(ST77XX_MAGENTA);
  screen.print(millis() / 1000);
  screen.setTextColor(ST77XX_WHITE);
  screen.print(" seconds.");
}

void mediabuttons() {
  // play
  screen.fillScreen(ST77XX_BLACK);
  screen.fillRoundRect(25, 10, 78, 60, 8, ST77XX_WHITE);
  screen.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_RED);
  delay(500);
  // pause
  screen.fillRoundRect(25, 90, 78, 60, 8, ST77XX_WHITE);
  screen.fillRoundRect(39, 98, 20, 45, 5, ST77XX_GREEN);
  screen.fillRoundRect(69, 98, 20, 45, 5, ST77XX_GREEN);
  delay(500);
  // play color
  screen.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_BLUE);
  delay(50);
  // pause color
  screen.fillRoundRect(39, 98, 20, 45, 5, ST77XX_RED);
  screen.fillRoundRect(69, 98, 20, 45, 5, ST77XX_RED);
  // play color
  screen.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_GREEN);
}