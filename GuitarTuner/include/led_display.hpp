#pragma once
#include <Arduino.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include <Wire.h> 
#include <Fonts/FreeSerifBold9pt7b.h>
class led_display
{
private:
    Adafruit_SSD1306 display; /* Object of class Adafruit_SSD1306 */
  
public:
    void init_oled();
    void oled_display(float text);
    led_display(/* args */);
    ~led_display();
};



    