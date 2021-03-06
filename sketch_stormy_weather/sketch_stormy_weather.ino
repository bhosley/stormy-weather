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
  pinMode(1, OUTPUT); //LED on Model A  
  pinMode(LED_PIN, OUTPUT); // Necessary call for Attiny85
  
  // Neopixel setup
  strip.begin();
  strip.show(); // Initialize all pixels to 'off' 
}

void loop()
{
  // Begin Ambient Noise
  if (true) {    // Thunder&Lightning Switch (Storm Scene Sequence)
    if (random(invStrikeChance) == 3) {    // Represents the Inverse probability of lightning strike
      int led = random(NUM_LEDS);
      for (int i = 0; i < 10; i++) {
        float brightness = random(1) == 1 ? 
          rma.addValue(y[currentIndex]) : sma.addValue(y[currentIndex]);

        float scaledWhite = abs(brightness*500);

        strip.setPixelColor(random(NUM_LEDS), strip.Color(scaledWhite, scaledWhite, scaledWhite));
        strip.show();
        delay(random(5, 100));

        currentIndex++;
        currentIndex = currentIndex % lenY;
        /*------------- Test ------------ */
        digitalWrite(1, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(1000);               // wait for a second
        digitalWrite(1, LOW);     // turn the LED off by making the voltage LOW
        delay(1000);               // wait for a second
        /*------------- Test ------------ */
        /* call for thunder clap */
      }
      invStrikeChance = 5;
    } else {
      invStrikeChance = 10;
    }
    for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, 0);
    }
    strip.show();
    delay(1000); /* Time between potential storm sequences; add read from potentiometer? */
  } // End Storm Sequence
}
