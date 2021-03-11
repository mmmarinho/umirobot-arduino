#include "UMIServo.h"
/**
UMIServo: a servo class by Murilo M. Marinho.
All rights reserved.
*/

int UMIServo::_convert_to_servo(const int& target_pos)
{
	return target_pos + 90;
}

void UMIServo::_write(const int& target_pos)
{
  curr_pos_ = target_pos;
  servo_.write(_convert_to_servo(target_pos));
}

void UMIServo::_write_smooth(const int& target_pos)
{
  if (target_pos > curr_pos_)
  {
    _write(curr_pos_ + 1);
	return;
  }
  if (target_pos < curr_pos_)
  {
    _write(curr_pos_ - 1);
	return;
  }
  _write(curr_pos_);
}

UMIServo::UMIServo(void):
  curr_pos_(0),
  min_pos_(-90),
  max_pos_(90),
  initialized_(false),
  error_(false),
  error_message_("")
{
}

void UMIServo::attach(const int& port)
{
  if(error_)
    return;
	
  if(!is_initialized())
	initialized_ = true;
	
  servo_.attach(port);
}

void UMIServo::write(const int& target_pos)
{
  if(error_)
    return;
  if(!is_initialized())
  {
	  error_=true;
	  error_message_ = "[Error] Called UMIServo::write() without calling UMIServo::attach().";
	  return;
  }	  
	
  if (target_pos > max_pos_)
  {
    _write_smooth(max_pos_);
    return;
  }
  if (target_pos < min_pos_)
  {
    _write_smooth(min_pos_);
    return;
  }
  _write_smooth(target_pos);
}

int UMIServo::read() const
{
  return curr_pos_;
}

bool UMIServo::is_initialized() const
{
	return initialized_;
}
bool UMIServo::is_error() const
{
	return error_;
}
String UMIServo::get_error_message() const
{
	return error_message_;
}