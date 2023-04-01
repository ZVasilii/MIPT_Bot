const int M_LEFT_PIN = 6;
const int M_RIGHT_PIN = 5;
const int ROT_RIGHT_PIN = 4;
const int ROT_LEFT_PIN = 7;
const int JOY_PIN = A0;


enum MOTOR {LEFT, RIGHT};
enum ROTATION {FORWARD, BACKWARD};

void setRotation(int rotationPin, ROTATION rotation);
void setSpeedRotation(MOTOR motor, ROTATION rotation, int speed);

void initMotorControl() {
  pinMode(M_LEFT_PIN, OUTPUT);
  pinMode(M_RIGHT_PIN, OUTPUT);
  pinMode(ROT_RIGHT_PIN, OUTPUT);
  pinMode(ROT_LEFT_PIN, OUTPUT);
}

int16_t rattlingOff(int16_t value)
{
  if (abs(value) < 5) 
    return 0;
  return value;  
}

int16_t rattlingOffCenter(int16_t value)
{
  int16_t middle = 256 / 2;
  if (abs(value - middle) < 8) 
    return 0;
  return value;  
}

void setPowerOnMotors(int16_t leftMotor, int16_t rightMotor)
{
  int16_t middle = 256 / 2;

  setSpeedRotation(LEFT, (leftMotor - middle) > 0 ? FORWARD : BACKWARD , rattlingOffCenter(leftMotor));
  setSpeedRotation(RIGHT, (rightMotor - middle) > 0 ? FORWARD : BACKWARD, rattlingOffCenter(rightMotor));
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
    rotationPin = ROT_RIGHT_PIN;
    motorPin = M_RIGHT_PIN;
  }
  setRotation(rotationPin, rotation);
  analogWrite(motorPin, speed);
}
