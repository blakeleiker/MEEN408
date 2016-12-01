#include "DCMOTOR.h"
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

DCMOTOR::DCMOTOR(int PWMNumberr, int EQEPNumberr){
	//Set up the PWM
	motorPWM = PWM(PWMNumberr, 1000000, 0);
	motorEQEP
}

DCMOTOR::void setAngle(int anglee);
DCMOTOR::int  getAngle();
DCMOTOR::void setAngleOffset(int offsett);
DCMOTOR::int  getAngleOffset();
DCMOTOR::void setVelocity( int torquee);
DCMOTOR::int  getVelocity();
DCMOTOR::void setPWMPeriod();
DCMOTOR::int  getPWMPeriod();
DCMOTOR::void setPWMDutyCycle();
DCMOTOR::int  getPWMDutyCycle();
DCMOTOR::void enable(int enablee);
