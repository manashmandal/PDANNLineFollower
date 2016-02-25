#include <LineFollower.h>


namespace std{
  ohserialstream cout(Serial);
}

using namespace std;

LineFollower::LineFollower(u_int *lm, u_int *rm, vector<u_int> &s)
{
  for (int i = 0; i < 2; i++){
    leftMotorPin[i] = lm[i];
    rightMotorPin[i] = rm[i];
  }
  sensors = s;
}

void LineFollower::to_string(void)
{
  for (u_int i = 0; i < sensors.size(); i++){
    cout << "sensor[" << i << "] = " << sensors[i] << endl;
  }
}
