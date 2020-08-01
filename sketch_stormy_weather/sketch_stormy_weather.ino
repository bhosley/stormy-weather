#include <Adafruit_NeoPixel.h>

#define LED_PIN 4
#define NUM_LEDS 2

Adafruit_NeoPixel lightning = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
int strikeDenominator = 10;

void setup() {
  // Neopixel setup
  lightning.begin();
  lightning.show(); 
}

void loop() {
  // Lightning Chance
  if (random(strikeDenominator) == 3) {
    int led = ranodm(NUM_LEDS);
    for (int i = 0; i < 10; i++) {
      lightningStrike(random(NUM_LEDS));
    }
    /* Increased odds for follow-on strike (decrease denominator) */
  } else {
    /* Decrease the odds of strike (Increase denominator) */
  }
  /* Turn off all Pixels */
  /* Delay between Loops */
}

/* To Black Function */
/* lightning strike function */
