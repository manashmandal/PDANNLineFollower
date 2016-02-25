#include <LineFollower.h>



//Sensor pins
vector <u_int> s{0, 1, 2, 3, 4, 5, 6, 7};
vector <u_int> s_6 {6, 5, 4, 3, 2, 1};
// vector <u_int> s_6 {1, 2, 3, 4, 5, 6};

u_int lm[] = {3, 5};
u_int rm[] = {6, 9};

LineFollower lineFollower(lm, rm, s_6);


void setup()
{
  LineFollowingRobot.set_motors_pins(lm, rm);
  LineFollowingRobot.set_sensors_pins(s_6);
  LineFollowingRobot.init();

  lineFollower.init();
  LineFollowingRobot.set_speed(120);
}

void loop()
{
  // LineFollowingRobot.wireless_control();
  // LineFollowingRobot.debug();
  // LineFollowingRobot.wireless_debug();
  // LineFollowingRobot.wireless_control();
  LineFollowingRobot.differential_drive();
}
