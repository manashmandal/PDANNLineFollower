#include <LineFollower.h>
#include <NeuralNetworkConfig.h>
#define NEURAL_NETWORK

const u_int _speed = 100;

//Sensor pins
vector <u_int> qtr{0, 1, 2, 3, 4, 5, 6, 7};

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
  weights();
}

#if defined(NEURAL_NETWORK)
void loop()
{
  weights();
  neural_network_drive();
}

#else
void loop()
{
  LineFollowingRobot.conditional_drive();
}
#endif
