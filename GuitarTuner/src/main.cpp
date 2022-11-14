#include <Arduino.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include <Wire.h> 
#include <Fonts/FreeSerifBold9pt7b.h>


#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET); /* Object of class Adafruit_SSD1306 */

// Sample Frequency in Hz
const float sample_freq = 20000;
float sample_freq_my;
const int len = 300;
short amp_arr[len]; //create vector of analog output values

int i,k;
long sum, sum_old;
int thresh = 0;
float freq_per = 0;
byte pd_state = 0;
unsigned long microseconds;
int period = 0;
int peak;


//definition of microphone properties (from MicSetup)
const int Mic = A3;       //Analog Input Pin on Arduino
const int BuiltInLed = 13;

void setup() {
  Serial.begin(115200);
  pinMode(7, INPUT);
  pinMode(Mic, INPUT);
  pinMode(BuiltInLed, OUTPUT);
  sum = 0;
  pd_state = 0;
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

void getSoundDataArr(short amp_arr[]){
    microseconds=0;  
    short temp=0;
    for (size_t i = 0; i < len; i++)
    {
        unsigned long before = millis();
        temp = analogRead(Mic);
        unsigned long after = millis();
        microseconds += (after - before);
        amp_arr[i]=temp;
    }
}

void autocorrelation(){
    peak=false;
  for(i=0; i < len; i++)
  {
    sum_old = sum;
    sum = 0;
    for(k=0; k < len-i; k++) sum += (amp_arr[k])*(amp_arr[k+i]);
    
    // Peak Detect State Machine
    if (pd_state == 2 && (sum-sum_old) <=0) 
    {
      
      peak=true;
      period = i;
      if (peak)
      {
        pd_state=3;
      }
    }
    if (pd_state == 1 && (sum > thresh) && (sum-sum_old) > 0) pd_state = 2;
    if (!i) {
      thresh = sum * 0.5;
      pd_state = 1;
    }
  }
  // Frequency identified in Hz
  sample_freq_my=(peak*1000)/microseconds;
  freq_per = sample_freq/period;
  display.clearDisplay(); /* Clear display */
  display.setFont(&FreeSerifBold9pt7b);
  display.setTextColor(WHITE);
  display.setTextSize(1); /* Select font size of text. Increases with size of argument. */
  display.setCursor(5,15);
  display.println(freq_per);
  display.display();
  
  }

void loop() {
  if (digitalRead(7) == LOW)
  {
    // display.clearDisplay();
    // display.setFont(&FreeSerifBold9pt7b);
    // display.setTextColor(WHITE);
    // display.setTextSize(1); /* Select font size of text. Increases with size of argument. */
    // display.setCursor(5,15);
    // display.println("Sygnal");
    // display.display();
    digitalWrite(BuiltInLed, HIGH);
    getSoundDataArr(amp_arr);
    autocorrelation();
    delay(3000);
  }else{
    // display.clearDisplay();
    // display.setFont(&FreeSerifBold9pt7b);
    // display.setTextColor(WHITE);
    // display.setTextSize(1); /* Select font size of text. Increases with size of argument. */
    // display.setCursor(5,15);
    // display.println("brak sygnalu");
    // display.display();
    digitalWrite(BuiltInLed, LOW);
  }

   
}
  


