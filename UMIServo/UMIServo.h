#include <Arduino.h>
#include <Servo.h>
/**
(c) 2020, Murilo M. Marinho, All rights reserved.
UMIServo: Controls a servo in the interval -60 to 60 degrees, with 
automatic smoothing.
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