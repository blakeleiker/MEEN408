#ifndef DCMOTOR_H
#define DCMOTOR_H

#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "PWM.h"
#include "EQEP.h"

class DCMOTOR {
 private:
  //Motor Parameters
  PWM motorPWM;
  EQEP motorEQEP;
  //Angle Tracking
  long int AbsCNT;
  long int AbsCNT_Prev;
  long int RelCNT;
  float angle;
  //Control Parameters
  float e;
  float e_i;
  float e_d;
  int motorOn;
 public:
  DCMOTOR(int PWMNumberr, int EQEPNumberr);
  ~DCMOTOR();
  void setAngle(int anglee);
  int  getAngle();
  void setAngleOffset(int offsett);
  int  getAngleOffset();
  void setVelocity( int torquee);
  int  getVelocity();
  void setPWMPeriod();
  int  getPWMPeriod();
  void setPWMDutyCycle();
  int  getPWMDutyCycle();
  void enable(int enablee);
};

#endif
