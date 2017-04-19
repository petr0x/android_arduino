#include <LiquidCrystal.h>
#include "FastLED.h"

#define NUM_LEDS 4
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  delay(1000);
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  lcd.begin(16, 2);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      String data = Serial.readString();
      if (data.substring(0,1) == "1") {
        lcd.clear();
        lcd.print(data.substring(1));
      }
      if (data.substring(0,1) == "2") {
        int xIndex = data.indexOf('x');
        int secondxIndex = data.indexOf('x', xIndex + 1);
    
        int r = data.substring(0, xIndex).toInt();
        int g = data.substring(xIndex + 1, secondxIndex).toInt();
        int b = data.substring(secondxIndex + 1).toInt();

        for(int i; i < NUM_LEDS; i++){
          leds[i] = CRGB(r,g,b);
        }

        
      }
      
    }
  }
}

