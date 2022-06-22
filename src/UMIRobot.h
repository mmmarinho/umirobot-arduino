#include "UMIServo/UMIServo.h"
/**
(c) 2020-2022, Murilo M. Marinho.

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
    int* q_;
	int* qd_;

	const int potentiometer_count_;
	int* potentiometer_ports_;
	int* potentiometer_values_;
	
	const int digital_in_count_;
	int* digital_in_ports_;
	int* digital_in_values_;
	
	const int servo_count_;
	UMIServo* servos_;
		
	Stream* serial_;

	bool initialized_;
	bool error_;
	String error_message_;
  public:
    UMIRobot(const int& servo_count,
		     const int& potentiometer_count,
		     const int& digital_in_count);
	~UMIRobot();

    void attachServo(const int& servo_index, const int& port);
	void attachServos(int ports[]);
	void attachPotentiometers(int ports[]);
	void attachDigitalInputs(int ports[]);

	void write(int qd[]);
	void update();
    int* read();
	
	void attachSerial(Stream& serial);

	void writeToSerial() const;
	void readFromSerial();
	
	int get_servo_count() const;
	int get_potentiometer_count() const;
	int get_digital_in_count() const;

	bool is_initialized() const;
	bool is_error() const;
	String get_error_message() const;
};

#endif