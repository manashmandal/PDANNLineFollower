#ifndef NEURAL_NETWORK_CONFIG_H_
#define NEURAL_NETWORK_CONFIG_H_
#include <LineFollower.h>


const int PatternCount = 1;
const int InputNodes = 8;
const int HiddenNodes = 10;
const int OutputNodes = 2;

double Input[PatternCount][InputNodes+1];

double Hidden[HiddenNodes];
double Output[OutputNodes];
double HiddenWeights[InputNodes+1][HiddenNodes];
double OutputWeights[HiddenNodes+1][OutputNodes];


void updateInput(void)
{
  LineFollowingRobot.read_line();
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
  HiddenWeights[0][0] = 4.24217;
  HiddenWeights[0][1] = -11.56230;
  HiddenWeights[0][2] = 5.07965 ;
  HiddenWeights[0][3] = 2.90034 ;
  HiddenWeights[0][4] =  26.49939;
  HiddenWeights[0][5] =  5.41574;
  HiddenWeights[0][6] = 2.19329 ;
  HiddenWeights[0][7] =  -3.45267;
  HiddenWeights[0][8] =  21.91952;
  HiddenWeights[0][9] = -6.57560 ;

  //Second
  HiddenWeights[1][0] = 1.54107 ;
  HiddenWeights[1][1] = 20.37917 ;
  HiddenWeights[1][2] = -4.46057 ;
  HiddenWeights[1][3] = -9.30750 ;
  HiddenWeights[1][4] = -0.68869 ;
  HiddenWeights[1][5] = 5.34653 ;
  HiddenWeights[1][6] = 8.55749 ;
  HiddenWeights[1][7] = 2.24979 ;
  HiddenWeights[1][8] =  5.58244;
  HiddenWeights[1][9] = 9.40761 ;

  //Third
  HiddenWeights[2][0] = 1.15439 ;
  HiddenWeights[2][1] =  10.74667;
  HiddenWeights[2][2] = 18.17214 ;
  HiddenWeights[2][3] = 2.91320 ;
  HiddenWeights[2][4] = 7.14709 ;
  HiddenWeights[2][5] = -3.12751 ;
  HiddenWeights[2][6] = 9.55273 ;
  HiddenWeights[2][7] = -1.32020 ;
  HiddenWeights[2][8] = 11.51749 ;
  HiddenWeights[2][9] = -6.96844 ;

  //Fourth
  HiddenWeights[3][0] = 1.70184 ;
  HiddenWeights[3][1] = -14.34860 ;
  HiddenWeights[3][2] = -12.25658 ;
  HiddenWeights[3][3] = 8.54586 ;
  HiddenWeights[3][4] = 12.05524 ;
  HiddenWeights[3][5] = -3.56456 ;
  HiddenWeights[3][6] = -1.70790 ;
  HiddenWeights[3][7] =  -6.49802;
  HiddenWeights[3][8] =  4.72596;
  HiddenWeights[3][9] = -2.44388 ;

  //Fifth
  HiddenWeights[4][0] = 4.54571 ;
  HiddenWeights[4][1] = -7.79218 ;
  HiddenWeights[4][2] =  -22.37191;
  HiddenWeights[4][3] = 8.11549 ;
  HiddenWeights[4][4] = -7.30386 ;
  HiddenWeights[4][5] = 5.62188 ;
  HiddenWeights[4][6] = 16.44036 ;
  HiddenWeights[4][7] = -2.42030 ;
  HiddenWeights[4][8] = 4.04853 ;
  HiddenWeights[4][9] = 2.02450 ;

  //Sixth
  HiddenWeights[5][0] = -4.30038 ;
  HiddenWeights[5][1] =  3.43618;
  HiddenWeights[5][2] =  -11.22073;
  HiddenWeights[5][3] =  2.34289;
  HiddenWeights[5][4] =  14.37478;
  HiddenWeights[5][5] =  -5.63753;
  HiddenWeights[5][6] = -28.99198 ;
  HiddenWeights[5][7] =  -4.75912;
  HiddenWeights[5][8] =  -14.26579;
  HiddenWeights[5][9] =  -3.87121;

  //Seventh
  HiddenWeights[6][0] =  -3.70616;
  HiddenWeights[6][1] = 3.40288 ;
  HiddenWeights[6][2] = -14.30912 ;
  HiddenWeights[6][3] =  3.63574;
  HiddenWeights[6][4] = 5.56789 ;
  HiddenWeights[6][5] = -5.99754 ;
  HiddenWeights[6][6] =  -8.04562;
  HiddenWeights[6][7] = -4.15216 ;
  HiddenWeights[6][8] =  -12.98620;
  HiddenWeights[6][9] = -3.51475 ;

  //Eighth
  HiddenWeights[7][0] = -4.49392 ;
  HiddenWeights[7][1] = 11.05428 ;
  HiddenWeights[7][2] = -15.66763 ;
  HiddenWeights[7][3] = 2.96874 ;
  HiddenWeights[7][4] = 10.29878 ;
  HiddenWeights[7][5] = 3.74424 ;
  HiddenWeights[7][6] = -0.34309 ;
  HiddenWeights[7][7] =  -2.34318;
  HiddenWeights[7][8] = -12.78464 ;
  HiddenWeights[7][9] =  -3.56498;

  //Bias
  HiddenWeights[8][0] = 8.5539 ;
  HiddenWeights[8][1] = -3.4794 ;
  HiddenWeights[8][2] = 5.3956 ;
  HiddenWeights[8][3] = -2.0654 ;
  HiddenWeights[8][4] =  -18.8746;
  HiddenWeights[8][5] = -17.2310 ;
  HiddenWeights[8][6] = 8.0457 ;
  HiddenWeights[8][7] = -8.5458 ;
  HiddenWeights[8][8] = 5.3477 ;
  HiddenWeights[8][9] = -8.0036 ;

  //Hidden to Output weights
  //1st
  OutputWeights[0][0] = -1.9999e+000 ;
  OutputWeights[0][1] = 4.2934e+001;

  //2nd
  OutputWeights[1][0] = 4.4046e-004;
  OutputWeights[1][1] = 1.9417e+001;

  //3rd
  OutputWeights[2][0] = -3.7500e+001;
  OutputWeights[2][1] = -1.2471e+001;

  //4th
  OutputWeights[3][0] = 5.8359e-004;
  OutputWeights[3][1] = 2.5449e+001;

  //5th
  OutputWeights[4][0] = 4.7963e-004;
  OutputWeights[4][1] = 2.3503e+001;

  //6th
  OutputWeights[5][0] = -1.5063e+001;
  OutputWeights[5][1] = 1.1414e+001;

  //7th
  OutputWeights[6][0] = 3.9991e+000;
  OutputWeights[6][1] = -1.5813e+001;

  //8th
  OutputWeights[7][0] = 7.2023e-002;
  OutputWeights[7][1] = -1.3357e+001;

  //9th
  OutputWeights[8][0] = -6.9990e+000;
  OutputWeights[8][1] = 5.3314e+001;

  //10th
  OutputWeights[9][0] = -5.3093e+000;
  OutputWeights[9][1] = 2.3156e+001;

  //Bias
  OutputWeights[10][0] = 22.200;
  OutputWeights[10][1] = 20.777;
}

#endif
