
const char CHANNEL = 7;
const long long PIPE = 0x1234567890LL;

using uc = unsigned char;
struct Command
{
  uc speedLeft{};
  uc speedRight{};

  Command() = default;
  Command(uc left, uc right) : speedLeft(left), speedRight(right)
  {}
};
