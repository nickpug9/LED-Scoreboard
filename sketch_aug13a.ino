#include <XPT2046_Touchscreen.h>

/**********************************************************************
 
 Interfacing ESP8266 NodeMCU with ILI9341 TFT display (240x320 pixel).
 This is a free software with NO WARRANTY.
 https://simple-circuit.com/

/**********************************************************************
/**********************************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 **********************************************************************/

#include <Arduino.h>

#include <Adafruit_GFX.h>       // include Adafruit graphics library
#include <Adafruit_ILI9341.h>   // include Adafruit ILI9341 TFT library
//#include <UTFT.h> 
//#include <URTouch.h>

#include <SPI.h>
 
#include <XPT2046_Touchscreen.h>

// For the ESP connection of touch
#define TFT_DC 2
#define TFT_CS 15
#define TFT_IRQ 5

//#define TFT_RST   D3     // TFT RST pin is connected to NodeMCU pin D3

// initialize ILI9341 TFT library with hardware SPI module
// SCK (CLK) ---> NodeMCU pin D5 (GPIO14)
// MOSI(DIN) ---> NodeMCU pin D7 (GPIO13)
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

//XPT2046 touch(/*cs=*/ 4, /*irq=*/ TFT_IRQ);
XPT2046_Touchscreen ts(TFT_CS, TFT_IRQ);



//==== Creating Objects
//UTFT    myGLCD(ILI9341_16,38,39,40,41); //Parameters should be adjusted to your Display/Schield model
//URTouch  myTouch( 6, 2, 4, 3, 2);

//==== Defining Variables
//extern uint8_t SmallFont[];
//extern uint8_t BigFont[];
//extern uint8_t SevenSegNumFont[];
//extern unsigned int bird01[0x41A];
//int x, y;
//char currentPage, selectedUnit;

//Ultrasonic Sensor
//const int VCC = 13;
//const int trigPin = 11;
//const int echoPin = 12;
//long duration;
//int distanceInch, distanceCm;

// RGB LEDs
//const int redLed = 10;
//const int greenLed = 9;
//const int blueLed = 8;
//int xR=38;
//int xG=38;
//int xB=38;

void setup() {

 
  
  int homeScore = 00;
  int awayScore = 00;
  int inning = 1;
  int balls = 0;
  int strikes = 0;
  int outs = 0;

   
// Initial setup
//  myGLCD.InitLCD();
//  myGLCD.clrScr();
//  myTouch.InitTouch(1); //SETS THE TOUCHSCREEN TO READ PROPERLY (PORTRAIT)
//  myTouch.setPrecision(PREC_MEDIUM);

  

 
  tft.begin();
  tft.setRotation(3);
    tft.fillScreen(ILI9341_BLACK);

 ts.begin();
  ts.setRotation(3);
   while (!Serial && (millis() <= 1000));

  // read diagnostics (optional but can help debug problems)
//  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
//  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
//  x = tft.readcommand8(ILI9341_RDMADCTL);
//  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
//  x = tft.readcommand8(ILI9341_RDPIXFMT);
//  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
//  x = tft.readcommand8(ILI9341_RDIMGFMT);
//  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
//  x = tft.readcommand8(ILI9341_RDSELFDIAG);
//  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 
//  
//  Serial.println(F("Benchmark                Time (microseconds)"));

//drawHomeScreen();  // Draws the Home Screen
//  currentPage = '0'; // Indicates that we are at Home Screen
//  selectedUnit = '0'; // Indicates the selected unit for the first example, cms or inches
//  Serial.println(initBaseballGame());


}
boolean wastouched = true;


void loop(void) {
  
//  Serial.println(initBaseballGame());
  boolean istouched = ts.touched();
 if (istouched) {
    TS_Point p = ts.getPoint();
    if (!wastouched) {
      tft.fillScreen(ILI9341_BLACK);
      tft.setTextColor(ILI9341_YELLOW);
      tft.setCursor(60, 80);
      tft.print("Touch");
    }
    tft.fillRect(100, 150, 140, 60, ILI9341_BLACK);
    tft.setTextColor(ILI9341_GREEN);
    tft.setCursor(100, 150);
    tft.print("X = ");
    tft.print(p.x);
    tft.setCursor(100, 180);
    tft.print("Y = ");
    tft.print(p.y);
    Serial.print(", x = ");
    Serial.print(p.x);
    Serial.print(", y = ");
    Serial.println(p.y);
  } else {
    if (wastouched) {
      tft.fillScreen(ILI9341_BLACK);
      tft.setTextColor(ILI9341_RED);
      tft.setCursor(120, 50);
      tft.print("No");
      tft.setCursor(80, 120);
      tft.print("Touch");
    }
    Serial.println("no touch");
  }
  wastouched = istouched;
  delay(100);
  
// Home Screen
//  if (currentPage == '0') {
//    if (myTouch.dataAvailable()) {
//      myTouch.read();
//      x=myTouch.getX(); // X coordinate where the screen has been pressed
//      y=myTouch.getY(); // Y coordinates where the screen has been pressed
//
//      tft.println(x, y);
      // If we press the Distance Sensor Button 
//      if ((x>=35) && (x<=285) && (y>=90) && (y<=130)) {
//        drawFrame(35, 90, 285, 130); // Custom Function -Highlighs the buttons when it's pressed
//        currentPage = '1'; // Indicates that we are the first example
//        myGLCD.clrScr(); // Clears the screen
//        drawDistanceSensor(); // It is called only once, because in the next iteration of the loop, this above if statement will be false so this funtion won't be called. This function will draw the graphics of the first example.
//      }
      // If we press the RGB LED Control Button 
//      if ((x>=35) && (x<=285) && (y>=140) && (y<=180)) {
//        drawFrame(35, 140, 285, 180);
//        currentPage = '2';
//        myGLCD.clrScr();
//        drawLedControl();
//      }  
     
//    }
//  }
}

//void drawHomeScreen() {
//  // Title
//  myGLCD.setBackColor(0,0,0); // Sets the background color of the area where the text will be printed to black
//  myGLCD.setColor(255, 255, 255); // Sets color to white
//  myGLCD.setFont(BigFont); // Sets font to big
//  myGLCD.print("Arduino TFT Tutorial", CENTER, 10); // Prints the string on the screen
//  myGLCD.setColor(255, 0, 0); // Sets color to red
//  myGLCD.drawLine(0,32,319,32); // Draws the red line
//  myGLCD.setColor(255, 255, 255); // Sets color to white
//  myGLCD.setFont(SmallFont); // Sets the font to small
//  myGLCD.print("by HowToMechatronics.com", CENTER, 41); // Prints the string
//  myGLCD.setFont(BigFont);
//  myGLCD.print("Select Example", CENTER, 64);
//  
//  // Button - Distance Sensor
//  myGLCD.setColor(16, 167, 103); // Sets green color
//  myGLCD.fillRoundRect (35, 90, 285, 130); // Draws filled rounded rectangle
//  myGLCD.setColor(255, 255, 255); // Sets color to white
//  myGLCD.drawRoundRect (35, 90, 285, 130); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
//  myGLCD.setFont(BigFont); // Sets the font to big
//  myGLCD.setBackColor(16, 167, 103); // Sets the background color of the area where the text will be printed to green, same as the button
//  myGLCD.print("DISTANCE SENSOR", CENTER, 102); // Prints the string
//  
//  // Button - RGB LED Control
//  myGLCD.setColor(16, 167, 103);
//  myGLCD.fillRoundRect (35, 140, 285, 180);
//  myGLCD.setColor(255, 255, 255);
//  myGLCD.drawRoundRect (35, 140, 285, 180);
//  myGLCD.setFont(BigFont);
//  myGLCD.setBackColor(16, 167, 103);
//  myGLCD.print("RGB LED CONTROL", CENTER, 152);
//  // Button - Birduino
//  myGLCD.setColor(16, 167, 103);
//  myGLCD.fillRoundRect (35, 190, 285, 230);
//  myGLCD.setColor(255, 255, 255);
//  myGLCD.drawRoundRect (35, 190, 285, 230);
//  myGLCD.setFont(BigFont);
//  myGLCD.setBackColor(16, 167, 103);
//  myGLCD.print("BIRDUINO GAME", CENTER, 202);
//}

unsigned long initBaseballGame() {
  unsigned long start = micros();
  int homeScore = 3;
  int awayScore = 2;
  int inning = 1;
  bool topOfInning = false;
  int balls = 2;
  int strikes = 1;
  int outs = 1;

  String homeTeam = "HOME";
  String awayTeam = "AWAY";

  Serial.println(getBaseballScoreboardTemplate(homeTeam, awayTeam ));
  Serial.println(updateBaseballScore(homeScore, awayScore, inning, topOfInning, balls, strikes, outs));
  
  return micros() - start;
}

unsigned long getBaseballScoreboardTemplate(String homeTeam, String awayTeam) {
    unsigned long start = micros();

  tft.drawFastVLine(tft.width()* 0.33,0,tft.height()* 0.6,ILI9341_YELLOW);
    tft.drawFastVLine(tft.width()* 0.66,0,tft.height()* 0.6,ILI9341_YELLOW);

  tft.drawFastHLine(0,tft.height()* 0.6,tft.width(),ILI9341_YELLOW);
    tft.drawFastHLine(0,tft.height()* 0.88,tft.width(),ILI9341_YELLOW);

      tft.setCursor(17, 100);
  tft.setTextSize(3);
    tft.println(homeTeam);

  tft.setCursor(123, 103);
  tft.setTextSize(2);
  tft.println("INNING");
  
  tft.setCursor(233, 100);
  tft.setTextSize(3);
  tft.println(awayTeam);


  tft.setCursor(22, 190);
  tft.setTextSize(2);
  tft.println("BALLS");
  tft.setCursor(120,190);
  tft.setTextSize(2);
  tft.println("STRIKES");
  tft.setCursor(245, 190);
  tft.setTextSize(2);
  tft.println("OUTS");

    tft.setCursor(7, 220);
  tft.setTextSize(2);
  tft.println("AB:Forman");

    tft.setCursor(165, 220);
  tft.setTextSize(2);
  tft.println("P:Wechsler");
  
  return micros() - start;

}

unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(ILI9341_BLACK);
  tft.fillScreen(ILI9341_RED);
  tft.fillScreen(ILI9341_GREEN);
  tft.fillScreen(ILI9341_BLUE);
  tft.fillScreen(ILI9341_BLACK);
  return micros() - start;
}

unsigned long updateBaseballScore(int home, int away, int inn,bool toi,int b, int s, int o) {
    unsigned long start = micros();

  tft.setTextColor(ILI9341_YELLOW);

  tft.setCursor(18, 35);
  tft.setTextSize(6);
  if(home < 10){tft.print("0");tft.print(home);}else{tft.println(home);}
  

  tft.setCursor(235, 35);
  tft.setTextSize(6);
  if(away < 10){tft.print("0");tft.print(away);}else{tft.println(away);}

  tft.setCursor(130, 40);
  tft.setTextSize(5);
  tft.println(inn);

  if(toi){
   tft.fillTriangle(175, 50, 165, 65, 185, 65, ILI9341_YELLOW);
   }else{
  
   tft.fillTriangle(165, 50, 185, 50, 175, 65, ILI9341_YELLOW);
  }

  Serial.println(getBalls(b));
  Serial.println(getStrikes(s));
  Serial.println(getOuts(o));


  return micros() - start;

    
}

unsigned long getBalls(int b){
  unsigned long start = micros();
  b = 2;
  for(int i=1; i <= 3; i++){
    if(i > b){
      tft.drawCircle(10+(i * 20 ), 165, 8, ILI9341_WHITE); 
    } else {
      tft.fillCircle(10+(i * 20 ), 165, 8, ILI9341_YELLOW);
    }
  }

  return micros() - start;
}

unsigned long getStrikes(int s){
  unsigned long start = micros();

  for(int i=1; i <= 2; i++){
    if(i > s){
      tft.drawCircle(130 +(i * 20 ), 165, 8, ILI9341_WHITE); 
    } else {
      tft.fillCircle(130 +(i * 20 ), 165, 8, ILI9341_YELLOW);
    }
  }

  return micros() - start;
}
unsigned long getOuts(int o){
  unsigned long start = micros();

  for(int i=1; i <= 2; i++){
    if(i > o){
      tft.drawCircle(235+(i * 20 ), 165, 8, ILI9341_WHITE); 
    } else {
      tft.fillCircle(235+(i * 20 ), 165, 8, ILI9341_YELLOW);
    }
  }


  return micros() - start;
}
unsigned long testText() {
  tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(ILI9341_RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
  return micros() - start;
}

unsigned long testLines(uint16_t color) {
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = tft.width(),
                h = tft.height();

  tft.fillScreen(ILI9341_BLACK);

  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing

  tft.fillScreen(ILI9341_BLACK);

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft.fillScreen(ILI9341_BLACK);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft.fillScreen(ILI9341_BLACK);

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);

  return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2) {
  unsigned long start;
  int           x, y, w = tft.width(), h = tft.height();

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for(y=0; y<h; y+=5) tft.drawFastHLine(0, y, w, color1);
  for(x=0; x<w; x+=5) tft.drawFastVLine(x, 0, h, color2);

  return micros() - start;
}

unsigned long testRects(uint16_t color) {
  unsigned long start;
  int           n, i, i2,
                cx = tft.width()  / 2,
                cy = tft.height() / 2;

  tft.fillScreen(ILI9341_BLACK);
  n     = min(tft.width(), tft.height());
  start = micros();
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    tft.drawRect(cx-i2, cy-i2, i, i, color);
  }

  return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  n = min(tft.width(), tft.height());
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    start = micros();
    tft.fillRect(cx-i2, cy-i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    tft.drawRect(cx-i2, cy-i2, i, i, color2);
  }

  return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      tft.fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
                w = tft.width()  + radius,
                h = tft.height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      tft.drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testTriangles() {
  unsigned long start;
  int           n, i, cx = tft.width()  / 2 - 1,
                      cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  n     = min(cx, cy);
  start = micros();
  for(i=0; i<n; i+=5) {
    tft.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      tft.color565(0, 0, i));
  }

  return micros() - start;
}

unsigned long testFilledTriangles() {
  unsigned long start, t = 0;
  int           i, cx = tft.width()  / 2 - 1,
                   cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for(i=min(cx,cy); i>10; i-=5) {
    start = micros();
    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(0, i, i));
    t += micros() - start;
    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(i, i, 0));
  }

  return t;
}

unsigned long testRoundRects() {
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  w     = min(tft.width(), tft.height());
  start = micros();
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    tft.drawRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(i, 0, 0));
  }

  return micros() - start;
}

unsigned long testFilledRoundRects() {
  unsigned long start;
  int           i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(ILI9341_BLACK);
  start = micros();
  for(i=min(tft.width(), tft.height()); i>20; i-=6) {
    i2 = i / 2;
    tft.fillRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(0, i, 0));
  }

  return micros() - start;
}
