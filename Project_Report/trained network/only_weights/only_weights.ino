
#include <math.h>
#include "NewPing.h"

const int PatternCount =1;
const int InputNodes = 5;
const int HiddenNodes = 10;
const int OutputNodes = 4;
float Input[PatternCount][InputNodes+1];
float O;

#define MAX_DISTANCE 400 
  double leftDistance, frontDistance, rightDistance,leftdownDistance,rightdownDistance;
  int leftMotor[] = {2, 3};
  int rightMotor[] = {5, 4};
 
NewPing leftSonar(9, 8, MAX_DISTANCE);
NewPing frontSonar (28, 29, MAX_DISTANCE);
NewPing rightSonar (13, 12, MAX_DISTANCE);
NewPing rightdownSonar (50, 51, MAX_DISTANCE);
NewPing leftdownSonar (52, 53, MAX_DISTANCE);

void updateDistance()
{
    Serial.println("Updating distances: ");
    leftDistance = leftSonar.ping() / US_ROUNDTRIP_CM;
    frontDistance = frontSonar.ping() / US_ROUNDTRIP_CM;
    rightDistance = rightSonar.ping() / US_ROUNDTRIP_CM;
    leftdownDistance = leftdownSonar.ping() / US_ROUNDTRIP_CM;
    rightdownDistance = rightdownSonar.ping() / US_ROUNDTRIP_CM;

    Serial.println("Front: " + String(frontDistance) + " cm");
    Serial.println("Left: " + String(leftDistance) + " cm");
    Serial.println("Right: " + String(rightDistance) + " cm");
    Serial.println("Leftdown: " + String(leftdownDistance) + " cm");
    Serial.println("Rightdown: " + String(rightdownDistance) + " cm");
}
void inputtarget()
{
  updateDistance();
  
  Input[0][0] = leftDistance;
  Input[0][1] = frontDistance;
  Input[0][2] = rightDistance;
  Input[0][3] = leftdownDistance;
  Input[0][4] = rightdownDistance;
  /**********************
  Bias for Hidden layer
  ***********************/
  Input[0][5]=1; 
}


int i, j, p, q, r;
int RandomizedIndex[PatternCount];
long  TrainingCycle;
float Rando;
float Accum;


float Hidden[HiddenNodes];
float Output[OutputNodes];
float HiddenWeights[InputNodes+1][HiddenNodes];
float OutputWeights[HiddenNodes+1][OutputNodes];
void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(3));
  for( p = 0 ; p < PatternCount ; p++ ) 
  {    
    RandomizedIndex[p] = p ;
  } 
  for (int i = 0; i < 2; i++){
        pinMode(leftMotor[i], OUTPUT);
        pinMode(rightMotor[i], OUTPUT);  
  }
  }
/**/
void setMotors(int l, int r)
{
    if (l >= 0 && r >= 0)
    {
        analogWrite(leftMotor[0], l);
        digitalWrite(leftMotor[1], LOW);
        analogWrite(rightMotor[0], r);
        digitalWrite(rightMotor[1], LOW);
    }

    else if (l < 0 && r < 0)
    {
        r = -r;
        l = -l;
        digitalWrite(leftMotor[0], LOW);
        analogWrite(leftMotor[1], l);
        digitalWrite(rightMotor[0], LOW);
        analogWrite(rightMotor[1], r);
    }

    else if (l > 0 && r < 0)
    {
        analogWrite(leftMotor[0], l);
        digitalWrite(leftMotor[1], LOW);
        digitalWrite(rightMotor[0], LOW);
        analogWrite(rightMotor[1], r);
    }

    else if (l < 0 && r > 0)
    {
        digitalWrite(leftMotor[0], LOW);
        analogWrite(leftMotor[1], l);
        analogWrite(rightMotor[0], r);
        digitalWrite(rightMotor[1], LOW);
    }

    else
    {
        digitalWrite(leftMotor[0], LOW);
        digitalWrite(leftMotor[1], LOW);
        digitalWrite(rightMotor[0], LOW);
        digitalWrite(rightMotor[1], LOW);
    }
}
void motordirection()
{
    if(O==Output[0])
  {
    Serial.println("front");
    setMotors(90,90);
    
  }

 else if(O==Output[1])
 {
  Serial.println("left");
  setMotors(0,0);
    delay(10);
    setMotors(0,150);
    delay(600);
    setMotors(0,0);
    delay(10);
 }
 else if(O==Output[2])
 {
  Serial.println("right");
  setMotors(0,0);
    delay(10);
  setMotors(150,0);
   delay(600);
    setMotors(0,0);
    delay(10);
 }
 else if(O==Output[3])
  {
    Serial.println("back");
    setMotors(0,0);
    delay(1000);
    setMotors(-150,-150);
  }
}
/**/
void toTerminal()
{
  for( p = 0 ; p < PatternCount ; p++ )
  { 
    Serial.println(); 
    Serial.print ("  Training Pattern: ");
    Serial.println (p);      
    Serial.print ("  Input ");
    for( i = 0 ; i <InputNodes ; i++ ) {
      Serial.print (Input[p][i], DEC);
      Serial.print (" ");
    }

    for( i = 0 ; i < HiddenNodes ; i++ ) {    
      Accum = HiddenWeights[InputNodes][i] ;
      for( j = 0 ; j <=InputNodes ; j++ ) {
        Accum += Input[p][j] * HiddenWeights[j][i] ;
      }
      Hidden[i] = 1.0/(1.0 + exp(-Accum)) ;
    }
    /****************************
    Bias for Output layer
    *****************************/
    Hidden[10]=3;


    for( i = 0 ; i < OutputNodes ; i++ ) {    
      Accum = OutputWeights[HiddenNodes][i] ;
      for( j = 0 ; j <=HiddenNodes ; j++ ) {
        Accum += Hidden[j] * OutputWeights[j][i] ;
      }
      Output[i] = 1.0/(1.0 + exp(-Accum)) ; 
    }
    Serial.print ("  Output ");
    for( i = 0 ; i < OutputNodes ; i++ ) {       
      Serial.print (Output[i],5);
      Serial.print (" ");
    }
  }
}  

void weights()
{

HiddenWeights[0][0]=-0.123846022463959;
HiddenWeights[0][1]=-0.00943216170181901;
HiddenWeights[0][2]=0.0529408461862648;
HiddenWeights[0][3]=-0.123864861930569;
HiddenWeights[0][4]=0.0113203978845675;
HiddenWeights[0][5]=-0.0209666967752174;
HiddenWeights[0][6]=0.260817369960935;
HiddenWeights[0][7]=0.0291801603463181;
HiddenWeights[0][8]=0.0687477758262452;
HiddenWeights[0][9]=-0.864956860786283;

HiddenWeights[1][0]=0.179099982170336;
HiddenWeights[1][1]=0.190785920164527;
HiddenWeights[1][2]=-0.0744938157672159;
HiddenWeights[1][3]=0.179125725651186;
HiddenWeights[1][4]=-0.212801209888234;
HiddenWeights[1][5]=0.0875463811271163;
HiddenWeights[1][6]=-0.132303846236798;
HiddenWeights[1][7]=-0.0852946696659487;
HiddenWeights[1][8]=-0.0188061560562580;
HiddenWeights[1][9]=-0.0188061560562580;

HiddenWeights[2][0]=-0.00476675710696819;
HiddenWeights[2][1]=-0.0541091777140061;
HiddenWeights[2][2]=0.00695561747720111;
HiddenWeights[2][3]=-0.00476836570700222;
HiddenWeights[2][4]=0.0574879315133481;
HiddenWeights[2][5]=0.314365219824837;
HiddenWeights[2][6]=0.0667069941885243;
HiddenWeights[2][7]=0.0445408186051293;
HiddenWeights[2][8]=-0.0460329218589721;
HiddenWeights[2][9]=0.00258787072128847;


HiddenWeights[3][0]=0.272066753019938;
HiddenWeights[3][1]=0.850182470535221;
HiddenWeights[3][2]=0.209714254537584;
HiddenWeights[3][3]=-0.424980325760586;
HiddenWeights[3][4]=-0.242110712630647;
HiddenWeights[3][5]=0.0126711577044135;
HiddenWeights[3][6]=-0.0241007773642907;
HiddenWeights[3][7]=0.122445369549045;
HiddenWeights[3][8]=0.0949081343997307;
HiddenWeights[3][9]=0.531629709341710;

HiddenWeights[4][0]=-0.226277786889064;
HiddenWeights[4][1]=-1.07942633839939;
HiddenWeights[4][2]=0.00374740660295069;
HiddenWeights[4][3]=-0.226097517221839;
HiddenWeights[4][4]=1.12138471351235;
HiddenWeights[4][5]=-0.958152167190698;
HiddenWeights[4][6]=-0.599777076292437;
HiddenWeights[4][7]=-0.0936665737257557;
HiddenWeights[4][8]=-0.0527183458031945;
HiddenWeights[4][9]=2.26661910952386;

/*******************
Bias weights for hidden layer
*******************/
HiddenWeights[5][0]=0.725672124264006;
HiddenWeights[5][1]=1.70097846731911;
HiddenWeights[5][2]=-2.12085948352692;
HiddenWeights[5][3]=4.21016572174907;
HiddenWeights[5][4]=-3.87932342110579;
HiddenWeights[5][5]=-0.267754558222678;
HiddenWeights[5][6]=-0.376779071410262;
HiddenWeights[5][7]=-0.900098303287815;
HiddenWeights[5][8]=-3.07183805010884;
HiddenWeights[5][9]=2.96963517757095;


OutputWeights[0][0]=-0.500056800850571;
OutputWeights[0][1]=0.500057086503142;
OutputWeights[0][2]=2.43680532615379e-07;
OutputWeights[0][3]=-5.29333104318573e-07;

OutputWeights[1][0]=0.499975812510385;
OutputWeights[1][1]=-0.499976500989936;
OutputWeights[1][2]=-0.500000126618779;
OutputWeights[1][3]=0.500000815098330;

OutputWeights[2][0]=0.000139421696241365;
OutputWeights[2][1]=-0.000139147698381058;
OutputWeights[2][2]=-1.74941539084963e-07;
OutputWeights[2][3]=-9.90563211608096e-08;

OutputWeights[3][0]=0.500074842730003;
OutputWeights[3][1]=-0.500074650708225;
OutputWeights[3][2]=-2.99427916670697e-07;
OutputWeights[3][3]=1.07406138182355e-07;

OutputWeights[4][0]=0.499993545348272;
OutputWeights[4][1]=-0.499941196329069;
OutputWeights[4][2]=-0.500052642014435;
OutputWeights[4][3]=0.500000292995232;

OutputWeights[5][0]=-2.00765286920690e-07;
OutputWeights[5][1]=0.500052648036074;
OutputWeights[5][2]=-0.500052433776244;
OutputWeights[5][3]=-1.34945432432261e-08;

OutputWeights[6][0]=6.41759346347621e-06;
OutputWeights[6][1]=-0.500059665715155;
OutputWeights[6][2]=0.500053023157881;
OutputWeights[6][3]=2.24963810352230e-07;

OutputWeights[7][0]=-6.45664492142652e-05;
OutputWeights[7][1]=6.46381440627136e-05;
OutputWeights[7][2]=-2.08508840804720e-07;
OutputWeights[7][3]=1.36813992286779e-07;

OutputWeights[8][0]=-5.76519959392238e-05;
OutputWeights[8][1]=5.76846518190429e-05;
OutputWeights[8][2]=7.46977759354211e-08;
OutputWeights[8][3]=-1.07353655702976e-07;

OutputWeights[9][0]=-0.499994065766919;
OutputWeights[9][1]=-5.91485259262892e-05;
OutputWeights[9][2]=0.500052981564082;
OutputWeights[9][3]=2.32728762916888e-07;

/**********************************
Bias weights for output layer
***********************************/
OutputWeights[10][0]=0.500017528740862;
OutputWeights[10][1]=-1.70779076485777e-05;
OutputWeights[10][2]=0.499999706371240;
OutputWeights[10][3]=-1.57204453092786e-07;
  }
void loop (){

inputtarget();
weights();

  toTerminal();

  O=max((float)max(Output[0],Output[1]),(float)max(Output[2],Output[3]));
  Serial.println(O,5);
  motordirection();
}


