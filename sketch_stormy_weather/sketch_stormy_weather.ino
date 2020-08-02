#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include <DFRobotDFPlayerMini.h>

#define LED_PIN = 1
#define RX_PIN = 2      // DFplayer RX to Arduino
#define TX_PIN = 3      // DFplayer TX to Arduino
#define BUSY_PIN = 4    // DFplayer BUSY
//#define ANALOG_IN = 5

#define NUM_SOUND_EFFECTS = 17  // Number of thunder sound effects on soundboard
#define NUM_LEDS = 5            // Number of lightning LEDs

SoftwareSerial mySoftwareSerial(RX_PIN, TX_PIN);
DFRobotDFPlayerMini myDFPlayer;

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
  // Set Pin Modes
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUSY_PIN, INPUT);

  // Begin Serial Output
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  // Attempt Connect to DFPlayer
  Serial.println(F("Initializing DFPlayer..."));
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin. Check connection and SD card, or reset the Arduino."));
    while (true);
  }

  // DFPlayer set-up
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.setTimeOut(500);                   // Set serial communictaion time out 500ms
  myDFPlayer.volume(30);                        // Set volume value (0~30).
  myDFPlayer.EQ(DFPLAYER_EQ_BASS);              // Set EQ to BASS (normal/pop/rock/jazz/classic/bass)
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);  // Set device we use SD as default
  myDFPlayer.enableDAC();                       // Enable On-chip DAC

  // Pixel set-up
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  // Initialize array of function pointers.
  functionPtrs[0] = simple_moving_average;
  functionPtrs[1] = random_moving_average;
}

void loop()
{
  if (random(chance) == 3) {
    lightningStrike();
    // TODO new thunder
    originalThunder();
    while (digitalRead(BUSY_PIN) == LOW) { 
      // Wait for the DFPlayer to finish playing the MP3 file
    }
    // Once there's been one strike, I make it more likely that there will be a second.
    chance = HIGH_STRIKE_LIKELIHOOD;
  } else {
    chance = LOW_STRIKE_LIKELIHOOD;
  }
  // Need Random Delay here (specifically for negative checks)
}

void lightningStrike() {
  
  int led = random(NUM_LEDS);
  for (int i = 0; i < 10; i++) {
    float brightness = callFunction(random(NUM_FUNCTIONS));
    float scaledWhite = abs(brightness*500);
    
    strip.setPixelColor(random(NUM_LEDS), strip.Color(scaledWhite, scaledWhite, scaledWhite));
    strip.show();
    delay(random(5, 100));
    currentDataPoint++;
    currentDataPoint = currentDataPoint%NUM_Y_VALUES;
  };
  strip.clear();
}

void thunderClap() {}

/**
 *  OLD FUNCTIONS 
 */

const int HIGH_STRIKE_LIKELIHOOD = 5;
const int LOW_STRIKE_LIKELIHOOD = 10;
int currentDataPoint = 0;
int chance = LOW_STRIKE_LIKELIHOOD;

// Simple moving average plot
int NUM_Y_VALUES = 17;

float yValues[] = {
  0,
  7,
  10,
  9,
  7.1,
  7.5,
  7.4,
  12,
  15,
  10,
  0,
  3,
  3.5,
  4,
  1,
  7,
  1
};

float simple_moving_average_previous = 0;
float random_moving_average_previous = 0;

float (*functionPtrs[10])(); //the array of function pointers
int NUM_FUNCTIONS = 2;

float callFunction(int index) {
  return (*functionPtrs[index])(); //calls the function at the index of `index` in the array
}

// https://en.wikipedia.org/wiki/Moving_average#Simple_moving_average
float simple_moving_average() {
  uint32_t startingValue = currentDataPoint;
  uint32_t endingValue = (currentDataPoint+1)%NUM_Y_VALUES;
  float simple_moving_average_current = simple_moving_average_previous + 
                                  (yValues[startingValue])/NUM_Y_VALUES - 
                                  (yValues[endingValue])/NUM_Y_VALUES;

  simple_moving_average_previous = simple_moving_average_current;
  return simple_moving_average_current;
}


// Same as simple moving average, but with randomly-generated data points.
float random_moving_average() {
  float firstValue = random(1, 10);
  float secondValue = random(1, 10);
  float random_moving_average_current = random_moving_average_previous +
                                  firstValue/NUM_Y_VALUES -
                                  secondValue/NUM_Y_VALUES;
  random_moving_average_previous = random_moving_average_current;

  return random_moving_average_current;
}

void originalThunder() {
  int thunderDelay = random (500, 3000);  // Min. and max. delay between flashing and playing sound
  int thunderFile = random (1, NUM_SOUND_EFFECTS);       // There are 17 soundfiles: 0001.mp3 ... 0017.mp3

  Serial.print(F("Pausing before playing thunder sound, milliseconds: "));
  Serial.println(thunderDelay);
  delay(thunderDelay);

  Serial.print(F("Playing thunder sound, file number: "));
  Serial.println(thunderFile);
  myDFPlayer.playMp3Folder(thunderFile);
  delay(1000); // Give the DFPlayer some time
}

/*

void originalLightning() {
  int flashCount = random (3, 15);        // Min. and max. number of flashes each loop
  int flashBrightnessMin =  10;           // LED flash min. brightness (0-255)
  int flashBrightnessMax =  255;          // LED flash max. brightness (0-255)

  int flashDurationMin = 1;               // Min. duration of each seperate flash
  int flashDurationMax = 50;              // Max. duration of each seperate flash

  int nextFlashDelayMin = 1;              // Min, delay between each flash and the next
  int nextFlashDelayMax = 150;            // Max, delay between each flash and the next

  Serial.println();
  Serial.print(F("Flashing, count: "));
  Serial.println( flashCount );

  for (int flash = 0 ; flash <= flashCount; flash += 1) { // Flashing LED strip in a loop, random count

    analogWrite(LED_PIN, random (flashBrightnessMin, flashBrightnessMax)); // Turn LED strip on, random brightness
    delay(random(flashDurationMin, flashDurationMax)); // Keep it tured on, random duration

    analogWrite(LED_PIN, 0); // Turn the LED strip off
    delay(random(nextFlashDelayMin, nextFlashDelayMax)); // Random delay before next flash
  }
}