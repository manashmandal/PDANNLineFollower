#include <LineFollower.h>



//Sensor pins
vector <u_int> s{0, 1, 2, 3, 4, 5, 6, 7};

u_int lm[] = {2, 3};
u_int rm[] = {4, 5};

LineFollower lineFollower(lm, rm, s);


void setup() {Serial.begin(9600);}
void loop()
{
  lineFollower.to_string();
  delay(500);

}
