#include <UMIRobot.h>

UMIRobot::UMIRobot(const int& dof):
  dof_(dof),
  q_(new int[dof_]),
  qd_(new int[dof_]),
  potentiometer_values_(new int[dof_]),
  potentiometer_ports_(new int[dof_]),
  servos_(new UMIServo[dof_]),
  initialized_(false),
  error_(false),
  error_message_("")
{
	for(int i=0;i<dof;i++)
	{
		q_[i]=0;
		qd_[i]=0;
		potentiometer_values_[i]=0;
		potentiometer_ports_[i]=0;
	}
}

UMIRobot::~UMIRobot()
{
  delete q_;
  delete qd_;
  delete servos_;
  delete potentiometer_ports_;
  delete potentiometer_values_;
}

void UMIRobot::attach(const int& servo_index, const int& port)
{
  if (servo_index > dof_)
    return;
  if (servo_index < 0)
    return;
  servos_[servo_index].attach(port);
}

void UMIRobot::attach_all(int ports[])
{
  for (int i = 0; i < dof_; i++)
  {
    servos_[i].attach(ports[i]);
  }  
}

void UMIRobot::set_potentiometer_ports(int ports[])
{
  for (int i = 0; i < dof_; i++)
  {
    potentiometer_ports_[i] = ports[i];
  }  
}

int UMIRobot::get_dof() const
{
  return dof_;
}

void UMIRobot::write(int qd[])
{
  for (int i = 0; i < dof_; i++)
  {
    qd_[i]=qd[i];
  }
}

void UMIRobot::update()
{
  if(error_)
	return;
	
  for (int i = 0; i < dof_; i++)
  {
    if(!servos_[i].is_initialized())
	{
	  error_=true;
	  error_message_ = "[Error] Called UMIRobot::write() without UMIRobot::attach() for all DoFs.";
	  return;
	}
	if(servos_[i].is_error())
	{
	  error_=true;
	  error_message_ = servos_[i].get_error_message();
	  return;
	}
  }
	
  for (int i = 0; i < dof_; i++)
  {
    q_[i] = servos_[i].read();
	servos_[i].write(qd_[i]);
	potentiometer_values_[i] = analogRead(potentiometer_ports_[i]);
  }
}

void UMIRobot::set_serial(Stream& stream)
{
	serial_ = &stream;
}

void UMIRobot::send_information_to_serial() const
{
  for (int i = 0; i < dof_; i++)
  {
    serial_->print(q_[i]);
    serial_->print(" ");
  }
  for (int i = 0; i < dof_; i++)
  {
    serial_->print(potentiometer_values_[i]);
	serial_->print(" ");
  }
  serial_->println("UMI");
}

void UMIRobot::get_qd_from_serial() 
{
  int qd[dof_];
  if (serial_->available())
  {
    for(int i=0;i<dof_;i++)
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