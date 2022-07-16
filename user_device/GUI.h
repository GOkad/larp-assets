/**
 * @file GUI.h
 * @brief TFT 1.8" ST7735 Display Library
 * @version 1.0
 * @date 2022-07-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * @brief Adafruit_ST7735 Special pin definitions
 */
  // TODO: Check and select other pins
  #define TFT_CS     D1
  #define TFT_RST    -1  // you can also connect this to the Arduino reset in which case, set this #define pin to -1!
  #define TFT_DC     D2

/**
 * @brief Color definitions
 */

// Some ready-made 16-bit ('565') color settings:
#define BLACK 0x0000
#define WHITE 0xFFFF
#define RED 0xF800
#define GREEN 0x07E0
#define BLUE 0x001F
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define ORANGE 0xFC00

// TODO: redefine colors for easier user
float p = 3.1415926;

// Initialize TFT screen class for 1.44" and 1.8" TFT with ST7735
Adafruit_ST7735 screen = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

/**
 * @brief Setup TFT screen
 * 
 */
void gui_setup () {

    // Initialize screen for 1.8" TFT
    screen.initR(INITR_BLACKTAB);

}

/**
 * @brief THESE ARE SOME EXAMPLES
 * TODO: MIX AND MATCH
 * 
 */
void testlines(uint16_t color) {
  screen.fillScreen(BLACK);
  for (int16_t x=0; x < screen.width(); x+=6) {
    screen.drawLine(0, 0, x, screen.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < screen.height(); y+=6) {
    screen.drawLine(0, 0, screen.width()-1, y, color);
    delay(0);
  }

  screen.fillScreen(BLACK);
  for (int16_t x=0; x < screen.width(); x+=6) {
    screen.drawLine(screen.width()-1, 0, x, screen.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < screen.height(); y+=6) {
    screen.drawLine(screen.width()-1, 0, 0, y, color);
    delay(0);
  }

  screen.fillScreen(BLACK);
  for (int16_t x=0; x < screen.width(); x+=6) {
    screen.drawLine(0, screen.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < screen.height(); y+=6) {
    screen.drawLine(0, screen.height()-1, screen.width()-1, y, color);
    delay(0);
  }

  screen.fillScreen(BLACK);
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
  screen.fillScreen(BLACK);
  for (int16_t y=0; y < screen.height(); y+=5) {
    screen.drawFastHLine(0, y, screen.width(), color1);
  }
  for (int16_t x=0; x < screen.width(); x+=5) {
    screen.drawFastVLine(x, 0, screen.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  screen.fillScreen(BLACK);
  for (int16_t x=0; x < screen.width(); x+=6) {
    screen.drawRect(screen.width()/2 -x/2, screen.height()/2 -x/2 , x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  screen.fillScreen(BLACK);
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
  screen.fillScreen(BLACK);
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
  screen.fillScreen(BLACK);
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
  screen.fillScreen(BLACK);
  screen.setCursor(0, 30);
  screen.setTextColor(RED);
  screen.setTextSize(1);
  screen.println("Hello World!");
  screen.setTextColor(YELLOW);
  screen.setTextSize(2);
  screen.println("Hello World!");
  screen.setTextColor(GREEN);
  screen.setTextSize(3);
  screen.println("Hello World!");
  screen.setTextColor(BLUE);
  screen.setTextSize(4);
  screen.print(1234.567);
  delay(1500);
  screen.setCursor(0, 0);
  screen.fillScreen(BLACK);
  screen.setTextColor(WHITE);
  screen.setTextSize(0);
  screen.println("Hello World!");
  screen.setTextSize(1);
  screen.setTextColor(GREEN);
  screen.print(p, 6);
  screen.println(" Want pi?");
  screen.println(" ");
  screen.print(8675309, HEX); // print 8,675,309 out in HEX!
  screen.println(" Print HEX!");
  screen.println(" ");
  screen.setTextColor(WHITE);
  screen.println("Sketch has been");
  screen.println("running for: ");
  screen.setTextColor(MAGENTA);
  screen.print(millis() / 1000);
  screen.setTextColor(WHITE);
  screen.print(" seconds.");
}

void mediabuttons() {
  // play
  screen.fillScreen(BLACK);
  screen.fillRoundRect(25, 10, 78, 60, 8, WHITE);
  screen.fillTriangle(42, 20, 42, 60, 90, 40, RED);
  delay(500);
  // pause
  screen.fillRoundRect(25, 90, 78, 60, 8, WHITE);
  screen.fillRoundRect(39, 98, 20, 45, 5, GREEN);
  screen.fillRoundRect(69, 98, 20, 45, 5, GREEN);
  delay(500);
  // play color
  screen.fillTriangle(42, 20, 42, 60, 90, 40, BLUE);
  delay(50);
  // pause color
  screen.fillRoundRect(39, 98, 20, 45, 5, RED);
  screen.fillRoundRect(69, 98, 20, 45, 5, RED);
  // play color
  screen.fillTriangle(42, 20, 42, 60, 90, 40, GREEN);
}

void rerenderScreenFunction()
{
  // Your code here
}

/**
 * @brief Main draw gui function
 * 
 */
void gui_draw () {

  // Draw on screen
  // Add all conditional rendering here

  /**
   * //Example of conditional rendering
   * 
   * bool rerender = false;
   * 
   * if ( rerender ) {
   *    // Defined before void gui_draw();
   *    rerenderScreenFunction( );
   * }
   * 
   * // ! NOTE !
   * // The Condition for rerendering MUST be in user_device.ino
   * // and `bool rerender` should be a global variable
   * // but it's ok while testing 
   * delay( 1000 );
   * // The screen will be rerendered every 2000ms
   * rerender = !rerender;
   * 
   */
    
  uint16_t time = millis();
  screen.fillScreen(BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  // large block of text
  screen.fillScreen(BLACK);
  testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", WHITE);
  delay(1000);

  // tft print function!
  tftPrintTest();
  delay(4000);

  // a single pixel
  screen.drawPixel(screen.width()/2, screen.height()/2, GREEN);
  delay(500);

  // line draw test
  testlines(YELLOW);
  delay(500);

  // optimized lines
  testfastlines(RED, BLUE);
  delay(500);

  testdrawrects(GREEN);
  delay(500);

  testfillrects(YELLOW, MAGENTA);
  delay(500);

  screen.fillScreen(BLACK);
  testfillcircles(10, BLUE);
  testdrawcircles(10, WHITE);
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