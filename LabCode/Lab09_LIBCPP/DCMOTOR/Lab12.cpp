#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <sstream>
using namespace std;

int main(){
	cout << "PWM eQEP Start" << endl;
	
	FILE *eQEPHandle = NULL;

	const char *eQEPString = "/sys/devices/platform/ocp/48304000.epwmss/48304180.eqep/position";
	char eQEPRead[10]={0};
	long int AbsCNT;
	long int AbsCNT_Prev;
	long int RelCNT;

	int init = 1;
	float angle = 0;
	float e = 0;
	float e_d = 0;
	float e_prev = 0;
	float e_i = 0;


	FILE *PWM0Handle = NULL;
	const char *PWM0Period = "/sys/class/pwm/pwmchip0/pwm0/period";
	const char *PWM0Dutycycle = "/sys/class/pwm/pwmchip0/pwm0/duty_cycle";
	const char *PWM0Enable = "/sys/class/pwm/pwmchip0/pwm0/enable";
	char *PWMPeriodText;
	char setValue[10];

	if((PWM0Handle=fopen(PWM0Period,"r+"))!=NULL){
		fwrite("10000000",sizeof(char),8,PWM0Handle);
		fclose(PWM0Handle);
	}

	if((PWM0Handle=fopen(PWM0Dutycycle,"r+"))!=NULL){
		fwrite("0",sizeof(char),1,PWM0Handle);
		fclose(PWM0Handle);
	}

	if((PWM0Handle=fopen(PWM0Enable,"r+"))!=NULL){
		fwrite("1",sizeof(char),1,PWM0Handle);
		fclose(PWM0Handle);
	}

	for(int i=0;i<5000;i++){

		int pulsewidth=0;
		//eQEP
		if((eQEPHandle=fopen(eQEPString,"r+"))!=NULL){
			fread(eQEPRead,sizeof(char),10,eQEPHandle);
			fclose(eQEPHandle);
			stringstream ss(eQEPRead);

			ss >> AbsCNT;
			if(init==1)
			{
				AbsCNT_Prev=AbsCNT;
				init=0;
				angle=0;
			}
			RelCNT=AbsCNT-AbsCNT_Prev;
			AbsCNT_Prev=AbsCNT;
			float gear_r=41552.4;
			angle+=(float)RelCNT/gear_r*360.0;

		} else{
			cout << "error" << endl;
		}

		e=45*(i/100)-angle;
		e_d=e-e_prev;
		e_prev=e;
		e_i+=e;
		float u=2000.0*e+50*e_d+10*e_i;  //The actual controller part
		pulsewidth=1460000+(int)u;

		if(pulsewidth<1000000)
		{
			pulsewidth=1000000;
		}
		else if(pulsewidth>2000000)
		{
			pulsewidth=2000000;
		}
		else
		{
			pulsewidth=pulsewidth;
		}

		cout << "angle: " << angle << " (e,e_d,e_i)=" << "(" << e << "," << e_d << "," << e_i << ")" << endl;
		sprintf(setValue,"%d",pulsewidth);
		if((PWM0Handle=fopen(PWM0Dutycycle,"r+"))!=NULL){
			fwrite(setValue,sizeof(char),sizeof(setValue),PWM0Handle);
			fclose(PWM0Handle);
		}

		usleep(20000); //sleep for 20 milliseconds (20000 microseconds)
	}

	if((PWM0Handle=fopen(PWM0Dutycycle,"r+"))!=NULL){
		fwrite("0",sizeof(char),1,PWM0Handle);
		fclose(PWM0Handle);
	}

	if((PWM0Handle=fopen(PWM0Enable,"r+"))!=NULL){
		fwrite("0",sizeof(char),1,PWM0Handle);
		fclose(PWM0Handle);
	}

	cout << "PWM eQEP End" << endl;
	return 0;
}
