# UMIRobot (Arduino)

[![arduino-library-badge](https://www.ardu-badge.com/badge/UMIRobot.svg?)](https://www.ardu-badge.com/UMIRobot)

This is a companion library for the [UMIRobot](https://mmmarinho.github.io/teaching/FEN-CO3982S3.html). 

The following script must be uploaded to the Arduino that is connected to the robot's servos.
**It will work out-of-the-box as long as the UMIRobot PCB is also used.**

If you build your own connection board, it might be necessary to change the `servo_ports[]` or `potentimeter_ports[]` to match your board.
```cpp
...
int servo_ports[] = {3, 5, 6, 9, 10, 11}; //<- Change here if needed
int potentiometer_ports[] = {0, 1, 2, 3, 4, 5}; //<- Change here if needed
...
```
