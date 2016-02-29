#include <LineFollower.h>
#define NEURAL_NETWORK

const u_int _speed = 100;

//Sensor pins
vector <u_int> s{0, 1, 2, 3, 4, 5, 6, 7};
vector <u_int> s_6 {6, 5, 4, 3, 2, 1};
vector <u_int> qtr{0, 1, 2, 3, 4, 5, 6, 7};
// vector <u_int> s_6 {1, 2, 3, 4, 5, 6};

u_int lm[] = {5, 3};
u_int rm[] = {6, 9};

LineFollower lineFollower(lm, rm, qtr);


/*
ANN Portion
*/
const int PatternCount = 11;
const int InputNodes = 8;
const int HiddenNodes = 9;
const int OutputNodes = 2;
const float LearningRate = 0.3;
const float Momentum = 0.9;
const float InitialWeightMax = 0.5;
const float Success = 0.0001;

 byte Input[PatternCount][InputNodes] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 1, 1}
};

 byte Target[PatternCount][OutputNodes] = {
  {0, 0},
  {70, 70},
  {0, 64},
  {0, 68},
  {0, 72},
  {0, 72},
  {64, 0},
  {68, 0},
  {72, 0},
  {72, 0}
};

int i, j, p, q, r;
int ReportEvery1000;
int RandomizedIndex[PatternCount];
long  TrainingCycle;
float Rando;
float Error;
float Accum;


float Hidden[HiddenNodes];
float Output[OutputNodes];
float HiddenWeights[InputNodes+1][HiddenNodes];
float OutputWeights[HiddenNodes+1][OutputNodes];
float HiddenDelta[HiddenNodes];
float OutputDelta[OutputNodes];
float ChangeHiddenWeights[InputNodes+1][HiddenNodes];
float ChangeOutputWeights[HiddenNodes+1][OutputNodes];


void setup()
{
  //NN config
  randomSeed(analogRead(3));
  ReportEvery1000 = 1;
  for( p = 0 ; p < PatternCount ; p++ ) {
    RandomizedIndex[p] = p ;
  }

  LineFollowingRobot.set_motors_pins(lm, rm);
  LineFollowingRobot.set_sensors_pins(qtr);
  LineFollowingRobot.init();

  lineFollower.init();
  LineFollowingRobot.set_speed(70);
}

int leftMotorSpeed = 0;
int rightMotorSpeed = 0;

void input_target(void)
{
  LineFollowingRobot.read_line();
  for (int i = 0; i < LineFollowingRobot.digitalReading.size(); i++)
  {
    Input[0][i] = LineFollowingRobot.digitalReading[i];
  }

  if (LineFollowingRobot.digitalReading[3] == 1 || LineFollowingRobot.digitalReading[4] == 1)
  {
    leftMotorSpeed = 70;
    rightMotorSpeed = 70;
  }

  else if (LineFollowingRobot.digitalReading[2] == 1)
  {
    leftMotorSpeed = 0;
    rightMotorSpeed = 64;
  }

  else if (LineFollowingRobot.digitalReading[1] == 1)
  {
      leftMotorSpeed = 0;
      rightMotorSpeed = 68;
  }

  else if (LineFollowingRobot.digitalReading[0] == 1)
  {
    leftMotorSpeed = 0;
    rightMotorSpeed = 72;
  }


  else if (LineFollowingRobot.digitalReading[5] == 1)
  {
    leftMotorSpeed = 64;
    rightMotorSpeed = 0;
  }

  else if (LineFollowingRobot.digitalReading[6] == 1)
  {
    leftMotorSpeed = 68;
    rightMotorSpeed = 0;
  }

  else if (LineFollowingRobot.digitalReading[7] == 1)
  {
    leftMotorSpeed = 72;
    rightMotorSpeed = 0;
  }

  else if (LineFollowingRobot.digitalReading[0] == 1 && LineFollowingRobot.digitalReading[1] == 1)
  {
    leftMotorSpeed = 0;
    rightMotorSpeed = 72;
  }

  else if (LineFollowingRobot.digitalReading[6] == 1 && LineFollowingRobot.digitalReading[7] == 1)
  {
    leftMotorSpeed = 72;
    rightMotorSpeed = 0;
  }

  else
  {
    leftMotorSpeed = 0;
    rightMotorSpeed = 0;
  }

  Target[0][0] = leftMotorSpeed;
  Target[0][1] = rightMotorSpeed;
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
