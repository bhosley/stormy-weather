#include <Adafruit_NeoPixel.h>

#define LED_PIN 4
#define NUM_LEDS 2

Adafruit_NeoPixel lightning = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
int strikeDenominator = 10;

void setup() {
  // Lightning setup
  lightning.begin();
  lightning.show(); 

  // TODO Rain Loop Setup
}

void loop() {
  // Lightning Chance
  if (random(strikeDenominator) == 3) {
    int led = ranodm(NUM_LEDS);
    for (int i = 0; i < 10; i++) {
      callLightning(random(NUM_LEDS));
      // TODO Call thunder interrupt
    }
    // TODO Increased odds for follow-on strike (decrease denominator) 
  } else {
    // TODO Decrease the odds of strike (Increase denominator)
  }
  // TODO Turn off all Pixels
  // TODO Delay between Loops
}

// To Black Function
// lightning strike function
// thunder sound interrupt
