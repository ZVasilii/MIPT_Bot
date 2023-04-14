
const char CHANNEL = 7;
const long long PIPE = 0x1234567890LL;

using uc = unsigned char;
struct Command
{
  uc speedLeft{};
  uc speedRight{};
  int LED_ON;
  int SERVO_ON;

  Command() = default;
  Command(uc left, uc right, int led_on, int servo_on) : speedLeft(left), speedRight(right), LED_ON(led_on), SERVO_ON(servo_on)
  {}
};
