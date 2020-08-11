#include <Arduino.h>
#include "MovingAverage.h"
#include "Adafruit_NeoPixel.h"

#define NUM_LEDS 4
#define LED_PIN 2

int invStrikeChance = 10;
int currentIndex = 0;
float y[] = { 0, 7, 10, 9, 7.1, 7.5, 7.4, 12, 15, 10, 0, 3, 3.5, 4, 1, 7, 1 }; // Using values from Molly Nicholas
int lenY = sizeof(y) / sizeof(y[0]);

RandomMovingAverage rma = RandomMovingAverage();
SimpleMovingAverage sma = SimpleMovingAverage();
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
    // Argument 1 = Number of pixels in NeoPixel strip
    // Argument 2 = Arduino pin number (most are valid)
    // Argument 3 = Pixel type flags, add together as needed:
    //   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
    //   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
    //   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
    //   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
    //   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
    
void setup()
{
  pinMode(1, OUTPUT); //LED on Model A, also used to signal thunder sound interrupt
  pinMode(LED_PIN, OUTPUT); // Necessary call for Attiny85
  
  // Neopixel setup
  pixels.begin();
  pixels.show(); // Initialize all pixels to 'off' 
}

void loop()
{
  if (random(invStrikeChance) == 3) {    // Represents the Inverse probability of lightning strike
    /*-------------  Lightning Strike  ------------ */
    for (int i = 0; i < 10; i++) {
      float brightness = random(1) == 1 ? 
        rma.addValue(y[currentIndex]) : sma.addValue(y[currentIndex]);

      float scaledWhite = abs(brightness*500);

      pixels.setPixelColor(random(NUM_LEDS), pixels.Color(scaledWhite, scaledWhite, scaledWhite));
      pixels.show();
      delay(random(5, 100));

      currentIndex++;
      currentIndex = currentIndex % lenY;
    }
    /*-------------  Lightning Strike  ------------ */
    for (int i = 0; i < NUM_LEDS; i++) {
      pixels.setPixelColor(i, 0);
    }
    pixels.show();
    /*------------- Signal for Thunder ------------ */
    digitalWrite(1, HIGH);
    delay(2000);
    digitalWrite(1, LOW);
    delay(1000);      
    /*------------- Signal for Thunder ------------ */
    invStrikeChance = 5; // Make follow-up strikes more likely
  } else {
    invStrikeChance = 10;
  }
  delay(1000); /* Time between potential storm sequences; add read from potentiometer? */
}