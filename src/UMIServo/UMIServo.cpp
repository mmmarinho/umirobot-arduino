#include "UMIServo.h"
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