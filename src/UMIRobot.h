#include "UMIServo/UMIServo.h"
/**
(c) 2020, Murilo M. Marinho, All rights reserved.
UMIRobot: controls a robot composed of one or more MMMServo.
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

    void attach(const int& servo_index, const int& port);
	void attach_all(int ports[]);
    int get_dof() const;
    void write(int qd[]);
	void update();
    int* read();
	
	void set_serial(Stream& serial);
	void set_potentiometer_ports(int ports[]);
	void send_information_to_serial() const;
	void get_qd_from_serial();
	
	bool is_initialized() const;
	bool is_error() const;
	String get_error_message() const;
};

#endif