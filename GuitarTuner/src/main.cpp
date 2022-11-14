#include <Arduino.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include <Wire.h> 
#include "arduinoFFT.h"
#include <Fonts/FreeSerifBold9pt7b.h>


#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET); /* Object of class Adafruit_SSD1306 */

#define SAMPLES 128             //SAMPLES-pt FFT. Must be a base 2 number. Max 128 for Arduino Uno.
#define SAMPLING_FREQUENCY 2048 //Ts = Based on Nyquist, must be 2 times the highest expected frequency.

 
arduinoFFT FFT = arduinoFFT();

//FFT related variable definition
unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[SAMPLES]; //create vector of size SAMPLES to hold real values
double vImag[SAMPLES]; //create vector of size SAMPLES to hold imaginary values

//definition of microphone properties (from MicSetup)
const int Mic = A3;       //Analog Input Pin on Arduino
const int BuiltInLed = 13;

void setup() {
  Serial.begin(115200);
  pinMode(7, INPUT);
  pinMode(Mic, INPUT);
  pinMode(BuiltInLed, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); /* Initialize display with address 0x3C */
//   display.clearDisplay(); /* Clear display */
//   display.setFont(&FreeSerifBold9pt7b);
//   display.setTextColor(WHITE);
//   display.setTextSize(1); /* Select font size of text. Increases with size of argument. */
//   display.setCursor(5,15);
//   display.println("GuitarTuner");
//   display.display();
  sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY)); //Period in microseconds 
//   delay(500);

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

    for(int i=0; i<SAMPLES; i++){  /*SAMPLING*/
        vReal[i] = analogRead(Mic);
        vImag[i] = 0;
        while(micros() < (microseconds + sampling_period_us)){

        }
    }

    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

    double Peak =FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
    Serial.println(Peak);
    // double Peak = analogRead(Mic);
    display.clearDisplay();
    display.setFont(&FreeSerifBold9pt7b);
    display.setTextColor(WHITE);
    display.setTextSize(1); /* Select font size of text. Increases with size of argument. */
    display.setCursor(5,15);
    display.println(Peak);
    display.display();
    // while(1);
    //Serial.println();
    
    //delay(3000);
}
  


