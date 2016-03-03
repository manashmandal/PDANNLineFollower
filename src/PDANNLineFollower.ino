#include <LineFollower.h>
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
  input_target();

  /******************************************************************
* Initialize HiddenWeights and ChangeHiddenWeights
******************************************************************/

  for( i = 0 ; i < HiddenNodes ; i++ ) {
    for( j = 0 ; j <= InputNodes ; j++ ) {
      ChangeHiddenWeights[j][i] = 0.0 ;
      Rando = float(random(100))/100;
      HiddenWeights[j][i] = 2.0 * ( Rando - 0.5 ) * InitialWeightMax ;
    }
  }
/******************************************************************
* Initialize OutputWeights and ChangeOutputWeights
******************************************************************/

  for( i = 0 ; i < OutputNodes ; i ++ ) {
    for( j = 0 ; j <= HiddenNodes ; j++ ) {
      ChangeOutputWeights[j][i] = 0.0 ;
      Rando = float(random(100))/100;
      OutputWeights[j][i] = 2.0 * ( Rando - 0.5 ) * InitialWeightMax ;

    }
  }
  Bluetooth.println("Initial/Untrained Outputs: ");
  toTerminal();
/******************************************************************
* Begin training
******************************************************************/

  for( TrainingCycle = 1 ; TrainingCycle < 2147483647 ; TrainingCycle++)
  {

/******************************************************************
* Randomize order of training patterns
******************************************************************/

    for( p = 0 ; p < PatternCount ; p++) {
      q = random(PatternCount);
      r = RandomizedIndex[p] ;
      RandomizedIndex[p] = RandomizedIndex[q] ;
      RandomizedIndex[q] = r ;
    }
    Error = 0.0 ;
/******************************************************************
* Cycle through each training pattern in the randomized order
******************************************************************/
    for( q = 0 ; q < PatternCount ; q++ ) {
      p = RandomizedIndex[q];

/******************************************************************
* Compute hidden layer activations
******************************************************************/

      for( i = 0 ; i < HiddenNodes ; i++ ) {
        Accum = HiddenWeights[InputNodes][i] ;
        for( j = 0 ; j < InputNodes ; j++ ) {
          Accum += Input[p][j] * HiddenWeights[j][i] ;
        }
        Hidden[i] = 1.0/(1.0 + exp(-Accum)) ;
      }

/******************************************************************
* Compute output layer activations and calculate errors
******************************************************************/

      for( i = 0 ; i < OutputNodes ; i++ ) {
        Accum = OutputWeights[HiddenNodes][i] ;
        for( j = 0 ; j < HiddenNodes ; j++ ) {
          Accum += Hidden[j] * OutputWeights[j][i] ;
        }
        Output[i] = 1.0/(1.0 + exp(-Accum)) ;
        OutputDelta[i] = (Target[p][i] - Output[i]) * Output[i] * (1.0 - Output[i]) ;
        Error += 0.5 * (Target[p][i] - Output[i]) * (Target[p][i] - Output[i]) ;
      }

/******************************************************************
* Backpropagate errors to hidden layer
******************************************************************/

      for( i = 0 ; i < HiddenNodes ; i++ ) {
        Accum = 0.0 ;
        for( j = 0 ; j < OutputNodes ; j++ ) {
          Accum += OutputWeights[i][j] * OutputDelta[j] ;
        }
        HiddenDelta[i] = Accum * Hidden[i] * (1.0 - Hidden[i]) ;
      }


/******************************************************************
* Update Inner-->Hidden Weights
******************************************************************/


      for( i = 0 ; i < HiddenNodes ; i++ ) {
        ChangeHiddenWeights[InputNodes][i] = LearningRate * HiddenDelta[i] + Momentum * ChangeHiddenWeights[InputNodes][i] ;
        HiddenWeights[InputNodes][i] += ChangeHiddenWeights[InputNodes][i] ;
        for( j = 0 ; j < InputNodes ; j++ ) {
          ChangeHiddenWeights[j][i] = LearningRate * Input[p][j] * HiddenDelta[i] + Momentum * ChangeHiddenWeights[j][i];
          HiddenWeights[j][i] += ChangeHiddenWeights[j][i] ;
        }
      }

/******************************************************************
* Update Hidden-->Output Weights
******************************************************************/

      for( i = 0 ; i < OutputNodes ; i ++ ) {
        ChangeOutputWeights[HiddenNodes][i] = LearningRate * OutputDelta[i] + Momentum * ChangeOutputWeights[HiddenNodes][i] ;
        OutputWeights[HiddenNodes][i] += ChangeOutputWeights[HiddenNodes][i] ;
        for( j = 0 ; j < HiddenNodes ; j++ ) {
          ChangeOutputWeights[j][i] = LearningRate * Hidden[j] * OutputDelta[i] + Momentum * ChangeOutputWeights[j][i] ;
          OutputWeights[j][i] += ChangeOutputWeights[j][i] ;
        }
      }
    }

/******************************************************************
* Every 1000 cycles send data to terminal for display
******************************************************************/
    ReportEvery1000 = ReportEvery1000 - 1;
    if (ReportEvery1000 == 0)
    {
      Bluetooth.println();
      Bluetooth.println();
      Bluetooth.print ("TrainingCycle: ");
      Bluetooth.print (TrainingCycle);
      Bluetooth.print ("  Error = ");
      Bluetooth.println (Error, 5);

      toTerminal();

      if (TrainingCycle==1)
      {
        ReportEvery1000 = 999;
      }
      else
      {
        ReportEvery1000 = 1000;
      }
    }


/******************************************************************
* If error rate is less than pre-determined threshold then end
******************************************************************/

    if( Error < Success ) break ;
  }
for( i = 0 ; i < HiddenNodes ; i++ ) {
    for( j = 0 ; j <= InputNodes ; j++ ) {

  Bluetooth.println(OutputWeights[j][i]);}}
  Bluetooth.println ();
  Bluetooth.println();
  Bluetooth.print ("TrainingCycle: ");
  Bluetooth.print (TrainingCycle);
  Bluetooth.print ("  Error = ");
  Bluetooth.println (Error, 5);

  toTerminal();

  Bluetooth.println ();
  Bluetooth.println ();
  Bluetooth.println ("Training Set Solved! ");
  Bluetooth.println ("--------");
  Bluetooth.println ();
  Bluetooth.println ();
  ReportEvery1000 = 1;
}

void toTerminal()
{

  for( p = 0 ; p < PatternCount ; p++ ) {
    Bluetooth.println();
    Bluetooth.print ("  Training Pattern: ");
    Bluetooth.println (p);
    Bluetooth.print ("  Input ");
    for( i = 0 ; i < InputNodes ; i++ ) {
      Bluetooth.print (Input[p][i], DEC);
      Bluetooth.print (" ");
    }
    Bluetooth.print ("  Target ");
    for( i = 0 ; i < OutputNodes ; i++ ) {
      Bluetooth.print (Target[p][i], DEC);
      Bluetooth.print (" ");
    }
/******************************************************************
* Compute hidden layer activations
******************************************************************/

    for( i = 0 ; i < HiddenNodes ; i++ ) {
      Accum = HiddenWeights[InputNodes][i] ;
      for( j = 0 ; j < InputNodes ; j++ ) {
        Accum += Input[p][j] * HiddenWeights[j][i] ;
      }
      Hidden[i] = 1.0/(1.0 + exp(-Accum)) ;
    }

/******************************************************************
* Compute output layer activations and calculate errors
******************************************************************/

    for( i = 0 ; i < OutputNodes ; i++ ) {
      Accum = OutputWeights[HiddenNodes][i] ;
      for( j = 0 ; j < HiddenNodes ; j++ ) {
        Accum += Hidden[j] * OutputWeights[j][i] ;
      }
      Output[i] = 1.0/(1.0 + exp(-Accum)) ;
    }
    Bluetooth.print ("  Output ");
    for( i = 0 ; i < OutputNodes ; i++ ) {
      Bluetooth.print (Output[i], 5);
      Bluetooth.print (" ");
    }
  }




}


#else
void loop()
{
  LineFollowingRobot.conditional_drive();
}
#endif
