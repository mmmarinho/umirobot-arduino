#include <Arduino.h>
#include <Servo.h>
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

#ifndef UMIServo_HEADER_GUARD
#define UMIServo_HEADER_GUARD

class UMIServo
{
  private:
    const int min_pos_;
    const int max_pos_;

    int port_;
    int curr_pos_;
    Servo servo_;
	
	int _convert_to_servo(const int& target_pos);
    void _write(const int& target_pos);
    void _write_smooth(const int& target_pos);

	bool initialized_;
	bool error_;
	String error_message_;

  public:
    UMIServo();

    void attach(const int& port); //Attach to a PWM port to control a servo.
    void write(const int& target_pos); //Write a value in degrees, -60 to 60.
  	int read() const; //Returns a value in degrees, -60 to 60.
	
	bool is_initialized() const;
	bool is_error() const;
	String get_error_message() const;
};

#endif