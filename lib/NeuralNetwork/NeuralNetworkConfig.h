#ifndef NEURAL_NETWORK_CONFIG_H_
#define NEURAL_NETWORK_CONFIG_H_
#include <LineFollower.h>

#define INPUT_BIAS 1
#define HIDDEN_BIAS 1

const int PatternCount = 1;
const int InputNodes = 8;
const int HiddenNodes = 10;
const int OutputNodes = 2;

double Input[PatternCount][InputNodes+1];

double Hidden[HiddenNodes+1];
double Output[OutputNodes];
double HiddenWeights[InputNodes+1][HiddenNodes];
double OutputWeights[HiddenNodes+1][OutputNodes];

//Variables
double Accum;


void updateInput(void)
{
  LineFollowingRobot.read_sensors();
  for (u_int i = 0; i < LineFollowingRobot.digitalReading.size(); i++){
    Input[0][i] = LineFollowingRobot.digitalReading[i];
  }
  //Bias
  Input[0][8] = 1;
}

void weights(void)
{
  //Input to Hidden Weights
  //Hidden Weights for first IR
  HiddenWeights[0][0] =0.025113 ;
  HiddenWeights[0][1] =-0.761469 ;
  HiddenWeights[0][2] = -0.054762 ;
  HiddenWeights[0][3] = 1.929800;
  HiddenWeights[0][4] =  0.896791;
  HiddenWeights[0][5] = -0.642489 ;
  HiddenWeights[0][6] = 2.283807 ;
  HiddenWeights[0][7] = -3.604985 ;
  HiddenWeights[0][8] = 1.723457 ;
  HiddenWeights[0][9] =  -1.394811;

  //Second
  HiddenWeights[1][0] = -0.321062 ;
  HiddenWeights[1][1] = -0.724505 ;
  HiddenWeights[1][2] =  1.516371;
  HiddenWeights[1][3] = -0.767078 ;
  HiddenWeights[1][4] = -1.187555 ;
  HiddenWeights[1][5] =  1.021865;
  HiddenWeights[1][6] =  -1.131159;
  HiddenWeights[1][7] = -1.998590 ;
  HiddenWeights[1][8] =  2.275912;
  HiddenWeights[1][9] =  0.562050;

  //Third
  HiddenWeights[2][0] =  -0.786959;
  HiddenWeights[2][1] =  -0.081098;
  HiddenWeights[2][2] = -1.879575 ;
  HiddenWeights[2][3] = 0.454331 ;
  HiddenWeights[2][4] =  -1.062709;
  HiddenWeights[2][5] = -1.092372 ;
  HiddenWeights[2][6] =  -0.779593;
  HiddenWeights[2][7] = -1.295421 ;
  HiddenWeights[2][8] =  -1.352029;
  HiddenWeights[2][9] =  1.942178;

  //Fourth
  HiddenWeights[3][0] = -1.649061 ;
  HiddenWeights[3][1] = 2.324182 ;
  HiddenWeights[3][2] = 0.847181 ;
  HiddenWeights[3][3] =  -2.225811;
  HiddenWeights[3][4] = 0.355119 ;
  HiddenWeights[3][5] = 0.863736 ;
  HiddenWeights[3][6] = 1.617657 ;
  HiddenWeights[3][7] = -0.254025 ;
  HiddenWeights[3][8] = 0.677678 ;
  HiddenWeights[3][9] = 1.868622 ;

  //Fifth
  HiddenWeights[4][0] = -1.018758 ;
  HiddenWeights[4][1] = -0.144537 ;
  HiddenWeights[4][2] = -2.582041 ;
  HiddenWeights[4][3] =  -1.409654;
  HiddenWeights[4][4] = -0.138546 ;
  HiddenWeights[4][5] = 1.797844;
  HiddenWeights[4][6] = 1.701960 ;
  HiddenWeights[4][7] = 0.621565 ;
  HiddenWeights[4][8] = -1.213992 ;
  HiddenWeights[4][9] = 1.645741 ;

  //Sixth
  HiddenWeights[5][0] =  0.687452;
  HiddenWeights[5][1] =  -1.621133;
  HiddenWeights[5][2] =  1.418583;
  HiddenWeights[5][3] = 1.517330 ;
  HiddenWeights[5][4] =  1.647353;
  HiddenWeights[5][5] = 0.370115 ;
  HiddenWeights[5][6] = -0.048096 ;
  HiddenWeights[5][7] =  0.469378;
  HiddenWeights[5][8] = 0.525366 ;
  HiddenWeights[5][9] = -0.811420 ;

  //Seventh
  HiddenWeights[6][0] = 0.153970 ;
  HiddenWeights[6][1] = -1.806422 ;
  HiddenWeights[6][2] =  0.755054;
  HiddenWeights[6][3] =  -1.545513;
  HiddenWeights[6][4] = -1.765307 ;
  HiddenWeights[6][5] = 0.110509 ;
  HiddenWeights[6][6] = -0.177388 ;
  HiddenWeights[6][7] =  1.461557;
  HiddenWeights[6][8] =  0.563469;
  HiddenWeights[6][9] = 0.697234 ;

  //Eighth
  HiddenWeights[7][0] =  -1.936623;
  HiddenWeights[7][1] =  -2.409954;
  HiddenWeights[7][2] =  0.318658;
  HiddenWeights[7][3] = 0.113455 ;
  HiddenWeights[7][4] = 2.136323 ;
  HiddenWeights[7][5] =  1.984139;
  HiddenWeights[7][6] =  0.013263;
  HiddenWeights[7][7] =  1.487560;
  HiddenWeights[7][8] =  1.346021;
  HiddenWeights[7][9] = 0.425384 ;

  //Bias
  HiddenWeights[8][0] =  -2.80142;
  HiddenWeights[8][1] =  0.72864;
  HiddenWeights[8][2] = 2.41547;
  HiddenWeights[8][3] =  1.69676;
  HiddenWeights[8][4] = -1.37024;
  HiddenWeights[8][5] =  -3.81070;
  HiddenWeights[8][6] =  2.21854;
  HiddenWeights[8][7] =  0.70060;
  HiddenWeights[8][8] =  2.70361;
  HiddenWeights[8][9] =  -4.25234;

  //Hidden to Output weights
  //1st
  OutputWeights[0][0] =-1.252983 ;
  OutputWeights[0][1] = 0.715766;

  //2nd
  OutputWeights[1][0] = -0.421231;
  OutputWeights[1][1] =0.058311 ;

  //3rd
  OutputWeights[2][0] =-0.205985 ;
  OutputWeights[2][1] =-0.834553 ;

  //4th
  OutputWeights[3][0] = -0.814466 ;
  OutputWeights[3][1] = -0.548837;

  //5th
  OutputWeights[4][0] =0.521854 ;
  OutputWeights[4][1] = 0.250546;

  //6th
  OutputWeights[5][0] = -2.152792 ;
  OutputWeights[5][1] = 0.659315;

  //7th
  OutputWeights[6][0] = -0.306374;
  OutputWeights[6][1] =  0.252961;

  //8th
  OutputWeights[7][0] =0.268343 ;
  OutputWeights[7][1] = -0.854261 ;

  //9th
  OutputWeights[8][0] =  -2.098765;
  OutputWeights[8][1] = 1.391521;

  //10th
  OutputWeights[9][0] = -0.595847;
  OutputWeights[9][1] = -0.996570;

  //Bias
  OutputWeights[10][0] = -0.088178;
  OutputWeights[10][1] = 0.781867;
}

void calculateOutput(void)
{
  for(int p = 0 ; p < PatternCount ; p++ )
  {
    for(int i = 0 ; i < HiddenNodes ; i++ ) {
      Accum = HiddenWeights[InputNodes][i];
      for(int j = 0 ; j < InputNodes ; j++ ) {
        Accum += Input[p][j] * HiddenWeights[j][i] ;
      }
      // Hidden[i] = 1.0/(1.0 + exp(-Accum)) ;

      //Tansig
      Hidden[i] = (2.0/ (1 + exp(-2 * Accum))) - 1;
    }
    /****************************
    Bias for Output layer
    *****************************/
    Hidden[10] = HIDDEN_BIAS;

    for(int i = 0 ; i < OutputNodes ; i++ ) {
      Accum = OutputWeights[HiddenNodes][i] ;
      for(int j = 0 ; j < HiddenNodes ; j++ ) {
        Accum += Hidden[j] * OutputWeights[j][i] ;
      }


      //Tansig
     Output[i] = (2.0/ (1 + exp(-2 * Accum))) - 1;
    }
  }
}

void printNeuralNetworkOutputViaBluetooth(void)
{
  updateInput();
  calculateOutput();
  Bluetooth.println("Left: " + String(Output[0] * 100));
  Bluetooth.println("Right: " + String(Output[1] * 100));
}

void neural_network_drive(void)
{
  updateInput();
  calculateOutput();
  int lspeed = Output[0] * 100;
  int rspeed = Output[1] * 100;
  if (lspeed < 0) lspeed = -lspeed;
  if (rspeed < 0) rspeed = -rspeed;
  LineFollowingRobot.forward(lspeed, rspeed);
  Bluetooth.println("LEFT: " + String(lspeed));
  Bluetooth.println("RIGHT: " + String(rspeed));
}

#endif
