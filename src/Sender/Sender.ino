#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "Common.h"

const char RFPin0 = 9;
const char RFPin1 = 10;
const char LED_PIN = 8;
const char SERVO_PIN = 2;
const char JOY_LEFT_PIN = A0;
const char JOY_RIGHT_PIN = A1;

RF24 rmSnd(RFPin0, RFPin1);


void setup() {
  rmSnd.begin();
  rmSnd.setChannel(1);
  rmSnd.setDataRate(RF24_1MBPS);
  rmSnd.setPALevel(RF24_PA_HIGH);
  rmSnd.openWritingPipe(0x1234567877LL);
  rmSnd.stopListening();
  pinMode(LED_PIN, INPUT_PULLUP);
  pinMode(SERVO_PIN, INPUT);

  //Serial.begin(9600);

}

void loop() {
  uc left = analogRead(JOY_LEFT_PIN) / 4;
  uc right = analogRead(JOY_RIGHT_PIN) / 4;
  int LED_ON = digitalRead(LED_PIN);
  int SERVO_ON = digitalRead(SERVO_PIN);
  
  
  Command cmd(left, right, LED_ON, SERVO_ON);
  rmSnd.write(&cmd, sizeof(cmd));
  //Serial.println(String(left) + " " + String(right) + String(SERVO_ON));

}
