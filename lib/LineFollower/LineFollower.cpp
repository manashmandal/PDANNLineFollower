#include <LineFollower.h>

//Objects created for line following robot and bluetooth
LineFollower LineFollowingRobot;
SoftwareSerial Bluetooth(RX, TX);

namespace std
{
  ohserialstream cout(Serial);
}

using namespace std;

//Initialize everything
void LineFollower::init(void)
{
  motors_init();
  sensors_init();
  serial_init(BAUD);
}

//========== MOTOR SECTION ==============
//Initialize motors
void LineFollower::motors_init(void)
{
  for (u_int i = 0; i < 2; i++)
  {
    pinMode(leftMotorPin[i], OUTPUT);
    pinMode(rightMotorPin[i], OUTPUT);
  }
}

//Run the motors
void LineFollower::set_motors(int lspeed, int rspeed)
{
  //Forward || Left || Right
  if (lspeed >= 0 && rspeed >= 0)
  {
    leftSpeed = lspeed;
    rightSpeed = rspeed;
    pwm(leftMotorPin[FRONT_PIN], leftSpeed);
    pwm(rightMotorPin[FRONT_PIN], rightSpeed);
    off(leftMotorPin[BACK_PIN]);
    off(rightMotorPin[BACK_PIN]);
  }

  //Right || Clockwise
  else if (lspeed >= 0 && rspeed < 0)
  {
    leftSpeed = lspeed;
    rightSpeed = -rspeed;
    pwm(leftMotorPin[FRONT_PIN], leftSpeed);
    off(leftMotorPin[BACK_PIN]);
    pwm(rightMotorPin[BACK_PIN], rightSpeed);
    off(rightMotorPin[FRONT_PIN]);
  }

  //Left || Anticlockwise
  else if (lspeed < 0 && rspeed >= 0)
  {
    leftSpeed = -lspeed;
    rightSpeed = rspeed;
    pwm(rightMotorPin[FRONT_PIN], rightSpeed);
    off(rightMotorPin[BACK_PIN]);
    pwm(leftMotorPin[BACK_PIN], leftSpeed);
    off(leftMotorPin[FRONT_PIN]);
  }

  //Backward
  else if (lspeed < 0 && rspeed < 0)
  {
    leftSpeed = -lspeed;
    rightSpeed = -rspeed;
    pwm(leftMotorPin[BACK_PIN], leftSpeed);
    pwm(rightMotorPin[BACK_PIN], rightSpeed);
    off(leftMotorPin[FRONT_PIN]);
    off(rightMotorPin[FRONT_PIN]);
  }

  //Stop
  else stop();

}

//Extra motor controls
void LineFollower::forward(u_int lspeed, u_int rspeed)
{
  leftSpeed = lspeed;
  rightSpeed = rspeed;
  pwm(leftMotorPin[FRONT_PIN], leftSpeed);
  pwm(rightMotorPin[FRONT_PIN], rightSpeed);
  off(leftMotorPin[BACK_PIN]);
  off(rightMotorPin[BACK_PIN]);
}

void LineFollower::backward(u_int lspeed, u_int rspeed)
{
  leftSpeed = lspeed;
  rightSpeed = rspeed;
  pwm(leftMotorPin[BACK_PIN], leftSpeed);
  pwm(rightMotorPin[BACK_PIN], rightSpeed);
  off(leftMotorPin[FRONT_PIN]);
  off(rightMotorPin[FRONT_PIN]);
}

void LineFollower::left(u_int rspeed)
{
  rightSpeed = rspeed;
  off(leftMotorPin[BACK_PIN]);
  off(leftMotorPin[FRONT_PIN]);
  pwm(rightMotorPin[FRONT_PIN], rightSpeed);
  off(rightMotorPin[BACK_PIN]);
}

void LineFollower::right(u_int lspeed)
{
  leftSpeed = lspeed;
  off(rightMotorPin[FRONT_PIN]);
  off(rightMotorPin[BACK_PIN]);
  pwm(leftMotorPin[FRONT_PIN], leftSpeed);
  off(leftMotorPin[BACK_PIN]);
}

void LineFollower::clockwise(u_int lspeed, u_int rspeed)
{
  leftSpeed = lspeed;
  rightSpeed = rspeed;
  pwm(leftMotorPin[FRONT_PIN], leftSpeed);
  off(leftMotorPin[BACK_PIN]);
  pwm(rightMotorPin[BACK_PIN], rightSpeed);
  off(rightMotorPin[FRONT_PIN]);
}

void LineFollower::anticlockwise(u_int lspeed, u_int rspeed)
{
  leftSpeed = lspeed;
  rightSpeed = rspeed;
  pwm(leftMotorPin[FRONT_PIN], leftSpeed);
  off(leftMotorPin[BACK_PIN]);
  pwm(rightMotorPin[BACK_PIN], rightSpeed);
  off(rightMotorPin[FRONT_PIN]);
}

//Set the motor pins
void LineFollower::set_motors_pins(u_int *lm, u_int *rm)
{
  for (u_int i = 0; i < 2; i++)
  {
    leftMotorPin[i] = lm[i];
    rightMotorPin[i] = rm[i];
  }
}

void LineFollower::stop(void)
{
  for (u_int i = 0; i < 2; i++)
  {
    off(leftMotorPin[i]);
    off(rightMotorPin[i]);
  }
}


/*
========= SENSOR ==============
*/
//Initialize sensors
void LineFollower::sensors_init(void)
{
  for (u_int i = 0; i < sensors.size(); i++)
  {
    pinMode(sensors[i], INPUT);
  }
}

void LineFollower::sensors_init(vector <u_int> &s)
{
  sensors = s;
  for (u_int i = 0; i < sensors.size(); i++) pinMode(sensors[i], INPUT);
}

void LineFollower::set_sensors_pins(vector <u_int> s)
{
  sensors_init(s);
}


/*
//  =========== CONSTRUCTOR ==========
*/
//Ctor
LineFollower::LineFollower(u_int *lm, u_int *rm, vector <u_int> &s)
: defaultSpeed(DEFAULT_SPEED)
{
  sensors = s;
  for (u_int i = 0; i < 2; i++)
  {
    leftMotorPin[i] = lm[i];
    rightMotorPin[i] = rm[i];
  }
}

//Initialize serial communication
void LineFollower::serial_init(u_int baud)
{
  Serial.begin(baud);
  Bluetooth.begin(baud);
}

//========== WIRELESS CONTROL ========
void LineFollower::wireless_control(void)
{
  if (Bluetooth.available() > 0)
  {
    command = Bluetooth.read();
  }

  switch (command)
  {
    case 'w':
      forward(defaultSpeed, defaultSpeed);
      break;
    case 's':
      backward(defaultSpeed, defaultSpeed);
      break;
    case 'a':
      left(defaultSpeed);
      break;
    case 'd':
      right(defaultSpeed);
      break;
    default:
      stop();
      break;
  }
}

void LineFollower::wireless_control(bool debug_mode)
{
  if (!debug_mode) wireless_control();
  else
  {
    if (Bluetooth.available() > 0)
    {
      command = Bluetooth.read();
      Serial.println("I received: " + String(command));
    }

    switch (command)
    {
      Bluetooth.println(command);
      case 'w':
        forward(defaultSpeed, defaultSpeed);
        Bluetooth.println("FORWARD");
        Serial.println("FORWARD");
        break;
      case 's':
        backward(defaultSpeed, defaultSpeed);
        Bluetooth.println("BACKWARD");
        Serial.println("BACKWARD");
        break;
      case 'a':
        left(defaultSpeed);
        Bluetooth.println("LEFT");
        Serial.println("LEFT");
        break;
      case 'd':
        right(defaultSpeed);
        Bluetooth.println("RIGHT");
        Serial.println("RIGHT");
        break;
      default:
        Bluetooth.println("STOP");
        Serial.println("STOP");
        stop();
        break;
    }
  }
}