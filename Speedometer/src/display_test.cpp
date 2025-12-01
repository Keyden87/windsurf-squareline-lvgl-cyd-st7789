#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);
  delay(1000); // Give serial monitor time to connect
  Serial.println("Display Test Starting...");

  // Initialize display
  tft.init();
  tft.setRotation(1);  // Try different rotations (0-3) if needed
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.println("Display Test");
  tft.println("------------");
  tft.println("If you see noise,");
  tft.println("try adjusting");
  tft.println("SPI frequency");
  tft.println("in setup.");
  
  // Draw some test patterns
  delay(2000);
  testFillScreen();
  delay(1000);
  testText();
  delay(1000);
  testLines(TFT_CYAN);
  delay(500);
  testFastLines(TFT_RED, TFT_BLUE);
  delay(500);
  testRects(TFT_GREEN);
  delay(500);
  testFilledRects(TFT_YELLOW, TFT_MAGENTA);
  delay(500);
  testCircles(10, TFT_BLUE);
  testFilledCircles(10, TFT_BLUE);
  delay(1000);
}

void loop() {
  // Cycle through colors
  static uint32_t lastChange = 0;
  static uint8_t color = 0;
  
  if (millis() - lastChange > 1000) {
    lastChange = millis();
    switch (color) {
      case 0: tft.fillScreen(TFT_RED); break;
      case 1: tft.fillScreen(TFT_GREEN); break;
      case 2: tft.fillScreen(TFT_BLUE); break;
      case 3: tft.fillScreen(TFT_WHITE); break;
      case 4: tft.fillScreen(TFT_BLACK); break;
    }
    color = (color + 1) % 5;
    
    // Show current settings
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(0, 0);
    tft.printf("Freq: %d Hz\n", tft.getSPIinstance().frequency() / 1000);
    tft.printf("Rotation: %d\n", tft.getRotation());
  }
  
  delay(10);
}

// Test functions from TFT_eSPI examples
void testFillScreen() {
  tft.fillScreen(TFT_BLACK);
  tft.fillScreen(TFT_RED);
  tft.fillScreen(TFT_GREEN);
  tft.fillScreen(TFT_BLUE);
  tft.fillScreen(TFT_BLACK);
}

void testText() {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(TFT_YELLOW);
  tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(TFT_RED);
  tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(TFT_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindewortles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
}

void testLines(uint16_t color) {
  tft.fillScreen(TFT_BLACK);
  
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, 0, x, tft.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, 0, tft.width()-1, y, color);
  }
  
  tft.fillScreen(TFT_BLACK);
  
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, 0, x, tft.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, 0, 0, y, color);
  }
}

void testFastLines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(TFT_BLACK);
  
  for (int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testRects(uint16_t color) {
  tft.fillScreen(TFT_BLACK);
  
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  }
}

void testFilledRects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(TFT_BLACK);
  
  for (int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
  }
}

void testCircles(uint8_t radius, uint16_t color) {
  tft.fillScreen(TFT_BLACK);
  
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testFilledCircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}
