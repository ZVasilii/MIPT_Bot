const int M_LEFT_PIN = 6;
const int M_RIGHT_PIN = 5;
const int ROT_RIGTH_PIN = 4;
const int ROT_LEFT_PIN = 7;
const int JOY_PIN = A0;


enum MOTOR {LEFT, RIGHT};
enum ROTATION {FORWARD, BACKWARD};

void setRotation(int rotationPin, ROTATION rotation);
void setSpeedRotation(MOTOR motor, ROTATION rotation, int speed);

void setup() {
  Serial.begin(9600);
  pinMode(M_LEFT_PIN, OUTPUT);
  pinMode(M_RIGHT_PIN, OUTPUT);
  pinMode(ROT_RIGTH_PIN, OUTPUT);
  pinMode(ROT_LEFT_PIN, OUTPUT);

}

void loop() {

  int rotation = FORWARD;
  int speed = analogRead(JOY_PIN);
  speed = map(speed, 430, 900, 0, 255);
  setSpeedRotation(LEFT, rotation, 127);
  setSpeedRotation(RIGHT, rotation, 127);

}


void setRotation(int rotationPin, ROTATION rotation)
{  
  if (rotation)
    digitalWrite(rotationPin, HIGH);
  else
    digitalWrite(rotationPin, LOW);
}

void setSpeedRotation(MOTOR motor, ROTATION rotation, int speed)
{
  int rotationPin = -1;
  int motorPin = -1;
  
  if (motor == LEFT)
  {
    rotationPin = ROT_LEFT_PIN;
    motorPin = M_LEFT_PIN;
  }
  else
  {
    rotationPin = ROT_RIGTH_PIN;
    motorPin = M_RIGHT_PIN;
  } 
  setRotation(rotationPin, rotation);
  analogWrite(motorPin, speed);  
}
