#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#include "Common.h"
#include "MotorControl.h"
#include "FastLED.h"

const char RFPin0 = 9;
const char RFPin1 = 10;

const int PIN_LED = 8;
const int SERVO_PIN = 2;
const int NUM_LEDS = 5;
const int LED_HOLD = 500;
const int LED_HOLD_double = 200;

int LED_state = 0;
int LED_ON;
int SERVO_ON;
CRGB leds[NUM_LEDS];
Servo srv;


void set_led_state_0()
{
  leds[0] = CRGB::Black;
  leds[1] = CRGB::Black;
  leds[2] = CRGB::White;
  leds[3] = CRGB::Red;
  leds[4] = CRGB::Red;
  LED_state = 0;
  FastLED.show();
}

void set_led_state_1()
{
  leds[0] = CRGB::Blue;
  leds[1] = CRGB::Blue;
  leds[2] = CRGB::White;
  leds[3] = CRGB::Black;
  leds[4] = CRGB::Black;
  LED_state = 1;
  FastLED.show();
}

void set_led_state_2()
{
  for (int i = 0; i < NUM_LEDS; i++)
    leds[i] = CRGB::Black;
  LED_state = 2;
  FastLED.show();
}

void toggle_led()
{
  if (LED_ON)
  {
    if (LED_state)
    {
      set_led_state_0();
    }
    else
      set_led_state_1();
  }
  else
  {
   set_led_state_2();
  }
    
}

RF24 rmRcv(RFPin0, RFPin1);


void setup() {
  initMotorControl();
  rmRcv.begin();
  rmRcv.setChannel(1);
  rmRcv.setDataRate(RF24_1MBPS);
  rmRcv.setPALevel(RF24_PA_HIGH);
  rmRcv.openReadingPipe(0, 0x1234567877LL);
  rmRcv.startListening();
  FastLED.addLeds<WS2812, PIN_LED, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  srv.attach(SERVO_PIN);

  Serial.begin(9600);
}

void loop() {

  static unsigned long lastTimestampSwitch = millis();
  
  if (millis() - lastTimestampSwitch > LED_HOLD)
  {
    toggle_led();
    lastTimestampSwitch = millis();
  }
  
  Command cmd;
  if (rmRcv.available())
  {
    rmRcv.read(&cmd, sizeof(cmd));
    //Serial.println(String(cmd.speedLeft) + " " + String(cmd.speedRight));
    LED_ON = cmd.LED_ON;
    SERVO_ON = cmd.SERVO_ON;
    setPowerOnMotors(cmd.speedLeft, cmd.speedRight);
    Serial.println(String(cmd.SERVO_ON));
    if (SERVO_ON)
      srv.write(80);
     else
      srv.write(180);

    // Serial.println(String(tmp[1]));
  }

}
