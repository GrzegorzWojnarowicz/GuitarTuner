#include <Arduino.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include <Wire.h> 
#include <Fonts/FreeSerifBold9pt7b.h>


#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET); /* Object of class Adafruit_SSD1306 */

void setup() {
  Serial.begin(115200);
  pinMode(7, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); /* Initialize display with address 0x3C */
  display.clearDisplay(); /* Clear display */
  display.setFont(&FreeSerifBold9pt7b);
  display.setTextColor(WHITE);
  display.setTextSize(1); /* Select font size of text. Increases with size of argument. */
  display.setCursor(5,15);
  display.println("GuitarTuner");
  display.display();
  delay(500);
   
}

void loop() {
  if (digitalRead(7) == LOW)
  {
    display.clearDisplay();
    display.setFont(&FreeSerifBold9pt7b);
    display.setTextColor(WHITE);
    display.setTextSize(1); /* Select font size of text. Increases with size of argument. */
    display.setCursor(5,15);
    display.println("Sygnal");
    display.display();
  }else{
    display.clearDisplay();
    display.setFont(&FreeSerifBold9pt7b);
    display.setTextColor(WHITE);
    display.setTextSize(1); /* Select font size of text. Increases with size of argument. */
    display.setCursor(5,15);
    display.println("brak sygnalu");
    display.display();
  }
  
  
}
