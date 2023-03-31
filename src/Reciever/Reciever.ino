#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "Common.h"

const char RFPin0 = 9;
const char RFPin1 = 10;

RF24 rmRcv(RFPin0, RFPin1);


void setup() {
  rmRcv.begin();
  rmRcv.setChannel(1);
  rmRcv.setDataRate(RF24_1MBPS);
  rmRcv.setPALevel(RF24_PA_HIGH);
  rmRcv.openReadingPipe(0, 0x1234567890LL);
  rmRcv.startListening();

  Serial.begin(9600);

}

void loop() {

  //Command cmd;
  uc tmp[2] = {37, 49};
  uc test = 0;
  if (rmRcv.available())
  {
    rmRcv.read(&test, sizeof(test));
    Serial.print(test);
    // Serial.println(String(tmp[1]));
  }

}
