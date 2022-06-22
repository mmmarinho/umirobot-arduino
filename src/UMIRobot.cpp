#include <UMIRobot.h>
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
UMIRobot::UMIRobot(const int& servo_count,
                   const int& potentiometer_count,
                   const int& digital_in_count) :
  q_(new int[servo_count]),
  qd_(new int[servo_count]),
  potentiometer_count_(potentiometer_count),
  potentiometer_ports_(new int[potentiometer_count]),
  potentiometer_values_(new int[potentiometer_count]),
  digital_in_count_(digital_in_count),
  digital_in_ports_(new int[digital_in_count]),
  digital_in_values_(new int[digital_in_count]),
  servo_count_(servo_count),
  servos_(new UMIServo[servo_count]),
  initialized_(false),
  error_(false),
  error_message_("")
{
	for(int i=0; i < servo_count; i++)
	{
		q_[i]=0;
		qd_[i]=0;
	}
	for (int i = 0; i < potentiometer_count; i++)
	{
		potentiometer_values_[i] = 0;
		potentiometer_ports_[i] = 0;
	}
	for (int i = 0; i < digital_in_count; i++)
	{
		digital_in_values_[i] = 0;
		digital_in_ports_[i] = 0;
	}
}

UMIRobot::~UMIRobot()
{
  delete q_;
  delete qd_;
  delete servos_;
  delete potentiometer_ports_;
  delete potentiometer_values_;
  delete digital_in_ports_;
  delete digital_in_values_;
}

void UMIRobot::attachServo(const int& servo_index, const int& port)
{
  if (servo_index > servo_count_)
    return;
  if (servo_index < 0)
    return;
  servos_[servo_index].attach(port);
}

void UMIRobot::attachServos(int ports[])
{
  for (int i = 0; i < servo_count_; i++)
  {
    servos_[i].attach(ports[i]);
  }  
}

void UMIRobot::attachPotentiometers(int ports[])
{
  for (int i = 0; i < potentiometer_count_; i++)
  {
    potentiometer_ports_[i] = ports[i];
  }  
}

void UMIRobot::attachDigitalInputs(int ports[])
{
	for (int i = 0; i < digital_in_count_; i++)
	{
		digital_in_ports_[i] = ports[i];
	}
}

int UMIRobot::get_servo_count() const
{
  return servo_count_;
}

int UMIRobot::get_potentiometer_count() const
{
	return potentiometer_count_;
}

int UMIRobot::get_digital_in_count() const
{
	return digital_in_count_;
}

void UMIRobot::write(int qd[])
{
  for (int i = 0; i < servo_count_; i++)
  {
    qd_[i]=qd[i];
  }
}

void UMIRobot::update()
{
  if(error_)
	return;
	
  for (int i = 0; i < servo_count_; i++)
  {
    if(!servos_[i].is_initialized())
	{
	  error_=true;
	  error_message_ = "[Error] Called UMIRobot::write() without UMIRobot::attach() for all servos.";
	  return;
	}
	if(servos_[i].is_error())
	{
	  error_=true;
	  error_message_ = servos_[i].get_error_message();
	  return;
	}
  }
	
  for (int i = 0; i < servo_count_; i++)
  {
    q_[i] = servos_[i].read();
	servos_[i].write(qd_[i]);
  }
  for (int i = 0; i < potentiometer_count_; i++)
  {
	  potentiometer_values_[i] = analogRead(potentiometer_ports_[i]);
  }
  for (int i = 0; i < digital_in_count_; i++)
  {
	  digital_in_values_[i] = digitalRead(digital_in_ports_[i]);
  }
}

void UMIRobot::attachSerial(Stream& stream)
{
	serial_ = &stream;
}

void UMIRobot::writeToSerial() const
{
  serial_->print(servo_count_);
  serial_->print(" ");
  for (int i = 0; i < servo_count_; i++)
  {
	serial_->print(q_[i]);
    serial_->print(" ");
  }
  serial_->print(potentiometer_count_);
  serial_->print(" ");
  for (int i = 0; i < potentiometer_count_; i++)
  {
    serial_->print(potentiometer_values_[i]);
	serial_->print(" ");
  }
  serial_->print(digital_in_count_);
  serial_->print(" ");
  for (int i = 0; i < digital_in_count_; i++)
  {
	serial_->print(digital_in_values_[i]);
	serial_->print(" ");
  }
  serial_->println("UMI");
}

void UMIRobot::readFromSerial() 
{
  int qd[servo_count_];
  if (serial_->available())
  {
    for(int i=0;i<servo_count_;i++)
    {
      qd[i]=serial_->parseInt();
    }

    if(serial_->read()=='\n')
    {
      write(qd);
    }
  }
}


int* UMIRobot::read()
{
  return q_;
}

bool UMIRobot::is_initialized() const
{
	return initialized_;
}
bool UMIRobot::is_error() const
{
	return error_;
}
String UMIRobot::get_error_message() const
{
	return error_message_;
}