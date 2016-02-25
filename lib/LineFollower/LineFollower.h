#ifndef LINE_FOLLOWER_H_
#define LINE_FOLLOWER_H_
#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include <serstream>
#include <iterator>


using namespace std;

//If inverse logic is defined
#if defined(INVERSE_LOGIC)
	#define INSIDE_LINE 0
	#define OUTSIDE_LINE 1
#else
	#define INSIDE_LINE 1
	#define OUTSIDE_LINE 0
#endif


typedef unsigned int u_int;

class LineFollower
{
private:
  u_int leftMotorPin[2];
  u_int rightMotorPin[2];
  u_int defaultSpeed;
  vector <u_int> sensors;

public:
  //Constructors
  LineFollower(void) {};
  LineFollower(u_int *lm, u_int *rm, vector <u_int> &s);

  //Initializer
  void serial_init(u_int b);
  void init(void);

  //Motor config functions
  void set_motors_pins(u_int *lm, u_int *rm);
  void set_motors(int lspeed, int rspeed);
  void motors_begin(void);

  //toString function
  void to_string(void);
};

extern LineFollower LineFollowingRobot;

#endif
