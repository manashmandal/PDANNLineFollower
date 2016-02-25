# Processing Code for data collection & wireless control

```processing
import processing.serial.*;
int value = 0;
int width = 50;
int height = 50;
final int baud = 9600;

Serial arduino;

void setup(){
  String arduinoPort = "COM12";
  println(Serial.list());
  arduino = new Serial(this, arduinoPort, baud);
}

char old_key = '0';
char new_key = '1';

//Checking if any key was pressed, initializing with a 'false'
boolean wasPressed = false;

void serialEvent(Serial port){
  String inByte = port.readStringUntil('\n');
  if (inByte != null) println(inByte);
}

void draw(){
  //Check if key is pressed
  //If the key is pressed store it to the new_key char variable
  //If the key is not equal to the key previously pressed then write the data in serialport
  //Setting the was_pressed as true
  //Else condition will run if no key is pressed
  //Now checking if any key was previously pressedr
  //If wasPressed is true that means we can now write a stop value character to the serialport
  //Setting new_key as the stop character
  //Setting wasPressed = false since because we have stopped the robot and don't want to send further signal for stopping it again [Blocking data overflow]
  if (keyPressed == true){
    new_key = key;
    if (new_key != old_key) {
      arduino.write(key);
    }
    wasPressed = true;
  } else {
    if (wasPressed == true){
      new_key = 'z';
      arduino.write('z');
      wasPressed = false;
    }
  }
  old_key = new_key;
}
```
