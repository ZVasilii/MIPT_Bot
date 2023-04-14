#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "Common.h"
#include "MotorControl.h"

const char RFPin0 = 9;
const char RFPin1 = 10;

RF24 rmRcv(RFPin0, RFPin1);


void setup() {
  initMotorControl();
  rmRcv.begin();
  rmRcv.setChannel(1);
  rmRcv.setDataRate(RF24_1MBPS);
  rmRcv.setPALevel(RF24_PA_HIGH);
  rmRcv.openReadingPipe(0, 0x1234567877LL);
  rmRcv.startListening();

  Serial.begin(9600);
}

void loop() {

  Command cmd;
  uc tmp[2] = {37, 49};
  uc test = 0;
  if (rmRcv.available())
  {
    rmRcv.read(&cmd, sizeof(cmd));
    Serial.println(String(cmd.speedLeft) + " " + String(cmd.speedRight));
    setPowerOnMotors(cmd.speedLeft, cmd.speedRight);
    // Serial.println(String(tmp[1]));
  }

}
