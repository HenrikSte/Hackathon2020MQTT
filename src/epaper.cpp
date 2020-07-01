#include "epaper.h"

#include GxEPD_BitmapExamples

ePaper::ePaper() :
  io(SPI, /*CS=5*/ PIN_CS, /*DC=*/ PIN_DC, /*RST=*/ PIN_RST),
  display(io, /*RST=*/ PIN_RST, /*BUSY=*/ PIN_BUSY)
{
  Serial.println(display.bm_default);
  Serial.println(io.name);
}


void ePaper::showFont(const char name[], const GFXfont* f)
{

  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(f);
  display.setCursor(0, 0);
  display.println();
  display.println(name);
  display.println(" !\"#$%&'()*+,-./");
  display.println("0123456789:;<=>?");
  display.println("@ABCDEFGHIJKLMNO");
  display.println("PQRSTUVWXYZ[\\]^_");
#if defined(HAS_RED_COLOR)
  display.setTextColor(GxEPD_RED);
#endif
  display.println("`abcdefghijklmno");
  display.println("pqrstuvwxyz{|}~ ");
  display.update();
  delay(5000);
}

/*
void ePaper::showFontCallback()
{
  const char* name = "FreeMonoBold9pt7b";
  const GFXfont* f = &FreeMonoBold9pt7b;
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(f);
  display.setCursor(0, 0);
  display.println();
  display.println(name);
  display.println(" !\"#$%&'()*+,-./");
  display.println("0123456789:;<=>?");
  display.println("@ABCDEFGHIJKLMNO");
  display.println("PQRSTUVWXYZ[\\]^_");
#if defined(HAS_RED_COLOR)
  display.setTextColor(GxEPD_RED);
#endif
  display.println("`abcdefghijklmno");
  display.println("pqrstuvwxyz{|}~ ");
}

*/

void ePaper::rederLabel( const String & data,  const String & layout)
{

}


void ePaper::showText( const GFXfont* f,
              const char* text)
{
  display.fillScreen(GxEPD_WHITE);
  #if defined(HAS_RED_COLOR)
    display.setTextColor(GxEPD_RED);
  #else
    display.setTextColor(GxEPD_BLACK);
  #endif
  display.setFont(f);
  display.setCursor(0, 0);
  display.println();
  display.println(text);
  display.update(); 
}

void ePaper::printHLine(uint16_t y, uint16_t width, uint16_t color) {
  display.fillRect(0,y,GxEPD_WIDTH,width,color);
}

uint16_t ePaper::printCenteredText(uint16_t y, const GFXfont* f, uint16_t color, const char* text) {
  display.setFont(f);
  int16_t x1,y1;
  uint16_t width,height;
  display.getTextBounds(text,0,y,&x1,&y1,&width,&height);
  //display.fillRect(x1,y1+height,width,height,GxEPD_BLACK);
  //color=GxEPD_WHITE;

  uint16_t offset = (400-width)/2;

  display.setCursor(offset,y+height);
  display.setTextColor(color);
  display.println(text);
  
  //return hight of line
  return height;
}

uint16_t ePaper::printLeftAlignedText(uint16_t y, const GFXfont* f, uint16_t color, const char* text) {
  display.setFont(f);
  int16_t x1,y1;
  uint16_t width,height;
  display.getTextBounds(text,0,y,&x1,&y1,&width,&height);
  //display.fillRect(x1,y1+height,width,height,GxEPD_BLACK);
  //color=GxEPD_WHITE;

  display.setCursor(0,y+height);
  display.setTextColor(color);
  display.println(text);

  //return hight of line
  return height;
}


void ePaper::printLabel()
{
  display.fillScreen(GxEPD_WHITE);
  // id
  printCenteredText(5,font18,GxEPD_BLACK,"BC200N01");

  //  top hline
  printHLine(40,4, GxEPD_BLACK);

  // details
  printLeftAlignedText(48,font9,GxEPD_BLACK,"Prod: HBP36748");
  printLeftAlignedText(66,font9,GxEPD_BLACK,"MO:   123467889999765");

  // statusbar
  printHLine(115,70, GxEPD_BLACK);
  printCenteredText(133,font24,GxEPD_RED,"NOT CLEAN");// TODO why is white is used instead of red

  // bottom hline
  printHLine(GxEPD_HEIGHT-40,4, GxEPD_BLACK);

  // batch
  printCenteredText(GxEPD_HEIGHT-30,font18,GxEPD_BLACK,"BTPRD0001");

  //update
  display.update();
}


/*
void ePaper::drawCornerTest()
{
  display.drawCornerTest();
  delay(5000);
  uint8_t rotation = display.getRotation();
  for (uint16_t r = 0; r < 4; r++)
  {
    display.setRotation(r);
    display.fillScreen(GxEPD_WHITE);
    display.fillRect(0, 0, 8, 8, GxEPD_BLACK);
    display.fillRect(display.width() - 18, 0, 16, 16, GxEPD_BLACK);
    display.fillRect(display.width() - 25, display.height() - 25, 24, 24, GxEPD_BLACK);
    display.fillRect(0, display.height() - 33, 32, 32, GxEPD_BLACK);
    display.update();
    delay(5000);
  }
  display.setRotation(rotation); // restore
}
*/

/*
#if defined(_GxGDEW042T2_H_)
void ePaper::showBitmapExample()
{
#if defined(__AVR)
  display.drawBitmap(BitmapExample1, sizeof(BitmapExample1));
#else
  display.drawExampleBitmap(BitmapExample1, sizeof(BitmapExample1));
  delay(2000);
  display.drawExampleBitmap(BitmapExample2, sizeof(BitmapExample2));
  delay(5000);
  display.fillScreen(GxEPD_WHITE);
  display.drawExampleBitmap(BitmapExample1, 0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK);
  display.update();
#endif
}
#endif

#if defined(_GxGDEW042Z15_H_)
#define HAS_RED_COLOR
void showBitmapExample()
{
#if defined(__AVR)
  display.drawBitmap(BitmapExample1, sizeof(BitmapExample1));
#else
  // draw black and red bitmap
  display.drawPicture(BitmapExample1, BitmapExample2, sizeof(BitmapExample1), sizeof(BitmapExample2));
  delay(5000);
  display.drawPicture(BitmapExample3, BitmapExample4, sizeof(BitmapExample3), sizeof(BitmapExample4));
  delay(5000);
  display.drawPicture(BitmapWaveshare_black, BitmapWaveshare_red, sizeof(BitmapWaveshare_black), sizeof(BitmapWaveshare_red));
  delay(5000);
  display.drawBitmap(BitmapExample1, sizeof(BitmapExample1));
  delay(2000);
  display.drawExampleBitmap(BitmapExample1, 0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK);
  display.update();
#endif
}
#endif


#if defined(_GxGDEW075T8_H_)
void showBitmapExample()
{
#if defined(__AVR)
  display.drawBitmap(BitmapExample1, sizeof(BitmapExample1));
#else
  display.drawExampleBitmap(BitmapExample1, sizeof(BitmapExample1));
  delay(2000);
  display.drawExampleBitmap(BitmapExample2, sizeof(BitmapExample2));
  delay(5000);
  display.fillScreen(GxEPD_WHITE);
  display.drawExampleBitmap(BitmapExample1, 0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK);
  display.update();
#endif
}
#endif

#if defined(_GxGDEW075Z09_H_)
#define HAS_RED_COLOR
void showBitmapExample()
{
#if defined(__AVR)
  display.drawBitmap(BitmapExample1, sizeof(BitmapExample1));
#elif defined(ARDUINO_GENERIC_STM32F103C)
  display.drawBitmap(BitmapExample1, sizeof(BitmapExample1));
#elif defined(ARDUINO_GENERIC_STM32F103V)
  display.drawExampleBitmap(BitmapExample1, sizeof(BitmapExample1));
  delay(2000);
  display.drawExamplePicture_3C(BitmapPicture_3C, sizeof(BitmapPicture_3C));
#else
  display.drawExampleBitmap(BitmapExample1, sizeof(BitmapExample1));
  delay(2000);
  display.drawExampleBitmap(BitmapExample2, sizeof(BitmapExample2));
  delay(5000);
  display.drawExamplePicture_3C(BitmapPicture_3C, sizeof(BitmapPicture_3C));
#endif
}
#endif

#if defined(_GxGDEW075T7_H_)
void showBitmapExample()
{
#if defined(__AVR)
  display.drawExampleBitmap(BitmapExample1, sizeof(BitmapExample1));
#else
  display.drawExampleBitmap(BitmapExample1, sizeof(BitmapExample1));
  delay(2000);
  display.drawExampleBitmap(BitmapExample2, sizeof(BitmapExample2));
  delay(5000);
  display.drawExampleBitmap(BitmapExample3, sizeof(BitmapExample1));
  delay(2000);
  display.drawExampleBitmap(BitmapExample4, sizeof(BitmapExample2));
  delay(5000);
  display.fillScreen(GxEPD_WHITE);
  display.drawExampleBitmap(BitmapExample1, 0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK);
  display.update();
#endif
}
#endif

#if defined(_GxGDEW075Z08_H_)
#define HAS_RED_COLOR
void showBitmapExample()
{
#if defined(__AVR) || defined(MCU_STM32F103C8)
  // draw (part of) black bitmap, not enough space for red
  display.drawPicture(BitmapExample1, 0, sizeof(BitmapExample1), 0);
#else
  // draw black and red bitmap
  display.drawExamplePicture(BitmapExample1, BitmapExample2, sizeof(BitmapExample1), sizeof(BitmapExample2));
  //delay(5000);
  //display.drawPicture(BitmapExample1, 0, sizeof(BitmapExample1), 0);
  //delay(5000);
  //display.drawPicture(0, BitmapExample2, 0, sizeof(BitmapExample2));
  //delay(5000);
  //display.drawExamplePicture(BitmapExample1, 0, sizeof(BitmapExample1), 0);
  //delay(5000);
  //display.drawExamplePicture(0, BitmapExample2, 0, sizeof(BitmapExample2));
  //delay(5000);
  //display.fillScreen(GxEPD_WHITE);
  //display.drawBitmap(0, 0, BitmapExample1, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK);
  //display.update();
  //delay(5000);
  //display.fillScreen(GxEPD_WHITE);
  //display.drawBitmap(0, 0, BitmapExample2, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK);
  //display.update();
  //display.drawExampleBitmap(BitmapExample1, 0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK);
  //display.updateWindow(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, false);
#endif

}

#endif
*/