#include <UMIServo.h>
#include <UMIRobot.h>


#include<UMIRobot.h>

const int DOFS=6;
UMIRobot robot(DOFS);
int servo_ports[] = {3, 5, 6, 9, 10, 11};
int potentiometer_ports[] = {0, 1, 2, 3, 4, 5};

void setup()
{
  robot.attach_all(servo_ports);
  robot.set_potentiometer_ports(potentiometer_ports);
  Serial.begin(115200);
  robot.set_serial(Serial);
}

void loop()
{
  robot.update();
  robot.get_qd_from_serial();
  robot.send_information_to_serial();
  delay(10);
}
