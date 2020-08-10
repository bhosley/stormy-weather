#include <Arduino.h>
#include "MovingAverage.h"
#include <Adafruit_NeoPixel.h>

#define NUM_LEDS = 4;
#define LED_PIN = 4;

int currentIndex = 0;
float y[] = {};
int lenY = sizeof(y) / sizeof(y[0]);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
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
  // Neopixel setup
  strip.begin();
  strip.show(); // Initialize all pixels to 'off' 
}

void loop()
{
  // Begin Ambient Noise
  if (true) {    // Thunder&Lightning Switch (Storm Scene Sequence)
    if (random(10) == 3) {    // Represents the Inverse probability of lightning strike
      int led = random(NUM_LEDS);
      for (int i = 0; i < 10; i++) {
        /* call for lightning strike and thunder clad */
        float brightness = /* callFunction(random(NUM_FUNCTIONS)); randomly call one of the moving randoms */;
        float scaledWhite = abs(brightness*500);

        strip.setPixelColor(random(NUM_LEDS), strip.Color(scaledWhite, scaledWhite, scaledWhite));
        strip.show();
        delay(random(5, 100));

        currentIndex++;
        currentIndex = currentIndex % lenY;
      }
      /* Set Strike chance high for increased odds of immediate follow-up */
    } else {
      /* Set Strike chance low*/
    }
    strip.clear();
    delay(1000); /* Time between potential storm sequences; add read from potentiometer? */
  } // End Storm Sequence
}