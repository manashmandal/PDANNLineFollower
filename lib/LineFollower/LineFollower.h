#ifndef LINE_FOLLOWER_H_
#define LINE_FOLLOWER_H_
#include <Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include <serstream>
#include <iterator>
#include <SoftwareSerial.h>

using namespace std;

//If inverse logic is defined
#if defined(INVERSE_LOGIC)
	#define INSIDE_LINE 0
	#define OUTSIDE_LINE 1
#else
	#define INSIDE_LINE 1
	#define OUTSIDE_LINE 0
#endif

///define front and back pin
#define FRONT_PIN 0
#define BACK_PIN 1

#define BAUD 9600
#define DEFAULT_SPEED 150
#define MULTIPLIER 1000

#define RX 10
#define TX 11

//Delay macro
#define SHORT_DELAY 100
#define LONG_DELAY 500

//Threshold
#define THRESHOLD 500

//add and subtract from or to this speed
#define spd 85
#define speed_factor 5
#define spd_factor 4
#define add_speed 120

//define input and output macro
#define input(pin) pinMode(pin, INPUT)
#define output(pin) pinMode(pin, OUTPUT)

//Define high low and pwm macro
#define pwm(pin, value) analogWrite(pin, value)
#define on(pin) digitalWrite(pin, HIGH)
#define off(pin) digitalWrite(pin, LOW)

#define short_delay delay(SHORT_DELAY)
#define long_delay delay(LONG_DELAY)


typedef unsigned int u_int;

class LineFollower
{
private:


  u_int leftMotorPin[2];
  u_int rightMotorPin[2];
  u_int defaultSpeed;
  vector <u_int> sensors;
	u_int leftSpeed;
	u_int rightSpeed;
	char command;
	u_int activeSensors;



public:
	//Digital and analog reading array
	vector <u_int> digitalReading;
	vector <u_int> analogReading;

  //Constructors
  LineFollower(void) :
	defaultSpeed(DEFAULT_SPEED),
	activeSensors(0)
	{
		leftSpeed = DEFAULT_SPEED;
		rightSpeed = DEFAULT_SPEED;
	};

  LineFollower(u_int *lm, u_int *rm, vector <u_int> &s);

  //Initializer
  void serial_init(u_int b);
  void init(void);
	void sensors_init(void);
	void sensors_init(vector <u_int> &s);
	void set_sensors_pins(vector <u_int> s);

  //Motor config functions
  void set_motors_pins(u_int *lm, u_int *rm);
  void set_motors(int lspeed, int rspeed);
  void motors_init(void);
	void stop(void);
	void set_speed(u_int dSpeed);

	//Extra motor controls
	void forward(u_int lspeed, u_int rspeed);
	void backward(u_int lspeed, u_int rspeed);
	void left(u_int rspeed);
	void right(u_int lspeed);
	void anticlockwise(u_int lspeed, u_int rspeed);
	void clockwise(u_int lspeed, u_int rspeed);

	bool check_left_turn(void);
	bool check_right_turn(void);

	//Bluetooth control
	void wireless_control(void);
	void wireless_control(bool debug_mode);

	//Debugging sensors
	void debug(void);
	void wireless_debug(void);


	//Line Following control
	void read_sensors(void);
	int read_line(void);
	void clear_reading(void);
	void differential_drive(void);
	void conditional_drive(void);

	int calculate_left_speed(void);
	int calculate_right_speed(void);

};

extern LineFollower LineFollowingRobot;
extern SoftwareSerial Bluetooth;

#endif
