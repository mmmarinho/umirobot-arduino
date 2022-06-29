#include<UMIRobot.h>

constexpr int servo_ports[] = {3, 5, 6, 9, 10, 11};
constexpr int potentiometer_ports[] = {0, 1, 2, 3, 4, 5};
constexpr int digital_in_ports[] = {2, 4, 7, 8, 12};
constexpr int digital_in_port_modes[] = {INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP};

constexpr int servo_port_count = get_size_of_array(servo_ports);
constexpr int potentiometer_port_count = get_size_of_array(potentiometer_ports);
constexpr int digital_in_port_count = get_size_of_array(digital_in_ports);
constexpr int digital_in_port_mode_count = get_size_of_array(digital_in_port_modes);

static_assert(digital_in_port_count == digital_in_port_mode_count, 
"Error: Adjust 'digital_in_ports' and 'digital_in_port_modes' so that they have the same amount of elements.");
static_assert(check_digital_in_port_modes(digital_in_port_modes),
"Error: The elements in 'digital_port_modes' should either be INPUT or INPUT_PULLUP");

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