#include <LineFollower.h>
#include <NeuralNetworkConfig.h>
// #define NEURAL_NETWORK

const u_int _speed = 100;

//Sensor pins
vector <u_int> s{0, 1, 2, 3, 4, 5, 6, 7};
vector <u_int> s_6 {6, 5, 4, 3, 2, 1};
vector <u_int> qtr{0, 1, 2, 3, 4, 5, 6, 7};
// vector <u_int> s_6 {1, 2, 3, 4, 5, 6};

u_int lm[] = {5, 3};
u_int rm[] = {6, 9};

LineFollower lineFollower(lm, rm, qtr);


void setup()
{

  LineFollowingRobot.set_motors_pins(lm, rm);
  LineFollowingRobot.set_sensors_pins(qtr);
  LineFollowingRobot.init();

  lineFollower.init();
  LineFollowingRobot.set_speed(75);
}


#if defined(NEURAL_NETWORK)
void loop()
{

}


#else
void loop()
{
  LineFollowingRobot.conditional_drive();
}
#endif
