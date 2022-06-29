# UMIRobot (Arduino)

[![arduino-library-badge](https://www.ardu-badge.com/badge/UMIRobot.svg?)](https://www.ardu-badge.com/UMIRobot)

This is a companion library for the [UMIRobot](https://mmmarinho.github.io/UMIRobot/).

The following script must be uploaded to the Arduino that is connected to the robot's servos.
**It will work out-of-the-box as long as the UMIRobot PCB is also used.**

If you build your own connection board or use a different Arduino board version, it might be necessary to change

- `servo_ports[]`
- `potentimeter_ports[]`
- `digital_in_ports[]`
- `digital_in_port_modes[]` 

to match your board.

```cpp
constexpr int servo_ports[] = {3, 5, 6, 9, 10, 11};
constexpr int potentiometer_ports[] = {0, 1, 2, 3, 4, 5};
constexpr int digital_in_ports[] = {2, 4, 7, 8, 12};
constexpr int digital_in_port_modes[] = {INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP,INPUT_PULLUP};
```
