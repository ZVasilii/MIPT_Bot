#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "Common.h"

const char RFPin0 = 9;
const char RFPin1 = 10;

RF24 rmSnd(RFPin0, RFPin1);


void setup() {
  rmSnd.begin();
  rmSnd.setChannel(1);
  rmSnd.setDataRate(RF24_1MBPS);
  rmSnd.setPALevel(RF24_PA_HIGH);
  rmSnd.openWritingPipe(0x1234567890LL);
  rmSnd.stopListening();

  Serial.begin(9600);

}

void loop() {
  uc left = analogRead(0) / 4;
  uc right = analogRead(1) / 4;
  
  Command cmd(left, right);
  Serial.println(String(left) + " " + String(right));
  rmSnd.write(&cmd, sizeof(cmd));

}
