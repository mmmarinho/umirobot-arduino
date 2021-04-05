#include "UMIServo/UMIServo.h"
/**
(c) 2020-2021, Murilo M. Marinho.

    This file is part of umirobot-arduino.

    umirobot-arduino is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    umirobot-arduino is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with umirobot-arduino.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef UMIRobot_HEADER_GUARD
#define UMIRobot_HEADER_GUARD

class UMIRobot
{
  private:
    const int dof_;
    int* q_;
	int* qd_;
	int* potentiometer_values_;
	int* potentiometer_ports_;
    UMIServo* servos_;
	
	Stream* serial_;

	bool initialized_;
	bool error_;
	String error_message_;
  public:
    UMIRobot(const int& dof);
	~UMIRobot();

    void attachServo(const int& servo_index, const int& port);
	void attachServos(int ports[]);
    int get_dof() const;
    void write(int qd[]);
	void update();
    int* read();
	
	void attachSerial(Stream& serial);
	void attachPotentiometers(int ports[]);
	void writeToSerial() const;
	void readFromSerial();
	
	bool is_initialized() const;
	bool is_error() const;
	String get_error_message() const;
};

#endif