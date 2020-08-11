#include <Arduino.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define THUNDER_PIN 2
#define BUSY_PIN 3          // DFplayer BUSY connected to pin 2
#define RX_DFP 4            // DFplayer RX to Arduino pin 4
#define TX_DFP 5            // DFplayer TX to Arduino pin 5

SoftwareSerial mySoftwareSerial(TX_DFP, RX_DFP); // Arduino RX, Arduino TX
DFRobotDFPlayerMini myDFPlayer;

void setup()
{
  pinMode(1, OUTPUT);
  pinMode(BUSY_PIN, INPUT);
  pinMode(THUNDER_PIN, INPUT);
  pinMode(RX_DFP, OUTPUT);
  pinMode(TX_DFP, INPUT);

  mySoftwareSerial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial);
  myDFPlayer.setTimeOut(500);                   // Set serial communictaion time out 500ms
  myDFPlayer.volume(30);                        // Set volume value (0~30).
  myDFPlayer.EQ(DFPLAYER_EQ_BASS);              // Set EQ to BASS (normal/pop/rock/jazz/classic/bass)
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);  // Set device we use SD as default
/*
  myDFPlayer.enableDAC();                       // Enable On-chip DAC
*/
  myDFPlayer.playMp3Folder(1);
}

void loop()
{
  /*
  if (digitalRead(BUSY_PIN) == LOW) {
    digitalWrite(1, HIGH);      // For Function Testing
    int rainFile = random (1, 13);       // There are x soundfiles: 0001.mp3 ... 00xx.mp3
    myDFPlayer.playMp3Folder(rainFile);
    digitalWrite(1, LOW);      // For Function Testing
    delay(500); // Give the DFPlayer some time
  }
  if (digitalRead(THUNDER_PIN) == HIGH) {
    digitalWrite(1, HIGH);      // For Function Testing
    int thunderFile = random (101, 116);   // There are x thunder files: 0101.mp3 ... 01xx.mp3
    myDFPlayer.playMp3Folder(thunderFile);
    //myDFPlayer.advertise(thunderFile);
    digitalWrite(1, LOW);      // For Function Testing
  }
  */
  if (digitalRead(THUNDER_PIN) == LOW) {
  digitalWrite(1, HIGH);
  delay(1000);
  digitalWrite(1, LOW);      // For Function Testing
  delay(1000);
  }
}
