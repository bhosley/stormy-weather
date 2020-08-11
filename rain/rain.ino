#include <Arduino.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define THUNDER_PIN 2

int RX_PIN = 4;    // DFplayer RX to Arduino pin 4
int TX_PIN = 5;    // DFplayer TX to Arduino pin 5
int BUSY_PIN = 3;  // DFplayer BUSY connected to pin 2

SoftwareSerial mySoftwareSerial(RX_PIN, TX_PIN);
DFRobotDFPlayerMini myDFPlayer;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(BUSY_PIN, INPUT);

  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  Serial.println(F("Initializing DFPlayer..."));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin. Check connection and SD card, or reset the Arduino."));
    while (true);
  }

  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.setTimeOut(500);                   // Set serial communictaion time out 500ms
  myDFPlayer.volume(30);                        // Set volume value (0~30).
  myDFPlayer.EQ(DFPLAYER_EQ_BASS);              // Set EQ to BASS (normal/pop/rock/jazz/classic/bass)
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);  // Set device we use SD as default
  myDFPlayer.enableDAC();                       // Enable On-chip DAC
}

void loop()
{
    if (digitalRead(BUSY_PIN) == LOW) {
        int rainFile = random (1, 2);       // There are x soundfiles: 0001.mp3 ... 00xx.mp3
            Serial.print(F("Playing rain sound, file number: "));
            Serial.println(rainFile);
        myDFPlayer.playMp3Folder(rainFile);
        delay(500); // Give the DFPlayer some time
    }
  if (digitalRead(THUNDER_PIN) == HIGH) {
      int thunderFile = random (100, 102);   // There are x thunder files: 0100.mp3 ... 01xx.mp3
            Serial.print(F("Playing thunder sound, file number: "));
            Serial.println(thunderFile);
      myDFPlayer.playMp3Folder(thunderFile);
      //myDFPlayer.advertise(thunderFile);
  }
}