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

  Command cmd(42, 53);
  uc snd[2] = {42, 53};
  uc a = 55;
  //Serial.print(String(snd[0]));
  //Serial.println(String(snd[1]));
  rmSnd.write(&a, sizeof(a));

}
