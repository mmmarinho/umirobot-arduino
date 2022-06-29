#include<UMIRobot.h>

constexpr int servo_ports[] = {3, 5, 6, 9, 10, 11};
constexpr int potentiometer_ports[] = {0, 1, 2, 3, 4, 5};
constexpr int digital_in_ports[] = {2, 4, 7, 8, 12};
constexpr int digital_in_port_modes[] = {INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP};

constexpr int servo_port_count = (sizeof(servo_ports) / sizeof(servo_ports[0]));
constexpr int potentiometer_port_count = (sizeof(potentiometer_ports) / sizeof(potentiometer_ports[0]));
constexpr int digital_in_port_count = (sizeof(digital_in_ports) / sizeof(digital_in_ports[0]));

UMIRobot robot(servo_port_count,
               potentiometer_port_count,
               digital_in_port_count);

void setup()
{
  robot.attachServos(servo_ports);
  robot.attachPotentiometers(potentiometer_ports);
  robot.attachDigitalInputs(digital_in_ports, digital_in_port_modes);
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