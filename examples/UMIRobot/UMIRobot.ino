#include<UMIRobot.h>

const int DOFS=6;
UMIRobot robot(DOFS);
int servo_ports[] = {3, 5, 6, 9, 10, 11};
int potentiometer_ports[] = {0, 1, 2, 3, 4, 5};

void setup()
{
  robot.attachServos(servo_ports);
  robot.attachPotentiometers(potentiometer_ports);
  Serial.begin(115200);
  robot.attachSerial(Serial);
}

void loop()
{
  robot.update();
  robot.readFromSerial();
  robot.writeToSerial();
  delay(10);
}