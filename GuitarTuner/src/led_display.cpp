#include "led_display.hpp"

led_display::led_display(/* args */)
{
    
}

led_display::~led_display()
{
}

void led_display::init_oled(){
    delay(500);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); /* Initialize display with address 0x3C */
    display.clearDisplay(); /* Clear display */
    display.setFont(&FreeSerifBold9pt7b);
    display.setTextColor(WHITE);
    display.setTextSize(1); /* Select font size of text. Increases with size of argument. */
    display.setCursor(5,15);
    display.println("GuitarTuner");
    display.display();
}

void led_display::oled_display(float text){
    display.clearDisplay(); /* Clear display */
    display.setFont(&FreeSerifBold9pt7b);
    display.setTextColor(WHITE);
    display.setTextSize(1); /* Select font size of text. Increases with size of argument. */
    display.setCursor(5,15);
    display.println(text);
    display.display();
}
