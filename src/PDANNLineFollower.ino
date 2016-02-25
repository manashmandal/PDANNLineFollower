#include <LineFollower.h>



//Sensor pins
vector <u_int> s{0, 1, 2, 3, 4, 5, 6, 7};

u_int lm[] = {3, 5};
u_int rm[] = {6, 9};

LineFollower lineFollower(lm, rm, s);


void setup()
{
  LineFollowingRobot.set_motors_pins(lm, rm);
  LineFollowingRobot.set_sensors_pins(s);
  LineFollowingRobot.init();

  lineFollower.init();
}

void loop()
{
  LineFollowingRobot.wireless_control();
}
