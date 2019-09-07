#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "BigButton.h"

static const uint8_t PIN_MP3_TX = 2;
static const uint8_t PIN_MP3_RX = 3;


BigButton bigGreenButton(A1);
BigButton bigRedButton(A0);

SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
DFRobotDFPlayerMini player;

void setup() {
  Serial.begin(9600); 
  softwareSerial.begin(9600);
  if (player.begin(softwareSerial)) {
    Serial.println("OK");
  } else {
    Serial.println("FAIL!");
  }
  player.volume(30);  //Set volume value. From 0 to 30
}

void loop() {
  processButton(bigGreenButton, "green", 7, 30);
  processButton(bigRedButton, "red", 5, 30);
}

int trackPlaying = -1;


void processButton(BigButton & bigButton, char * txt, int trackNo, int intVolume) {
  switch (bigButton.checkButton()) {
    case BUTTON_UP:
      Serial.print(txt);
      Serial.println(" up");
      break;
      
    case BUTTON_UP_DOWN:
      Serial.print(txt);
      Serial.print(player.available());
      Serial.println(" mid down");
      break;
      
    case BUTTON_DOWN:
      Serial.print(txt);
      Serial.println(" down");
      
      if (trackPlaying != trackNo) {
        player.volume(intVolume);
        player.play(trackNo);
        trackPlaying = trackNo;
      } else {
        player.stop();
        trackPlaying = -1;
      }
      break;
      
    case BUTTON_DOWN_UP:
      Serial.print(txt);
      Serial.println(" mid up");
      break;
  }
}
