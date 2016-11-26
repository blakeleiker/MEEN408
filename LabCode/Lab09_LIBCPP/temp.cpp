#include "GPIO.h"
#include<iostream>
#include<unistd.h>
#include<string>

int main()
{
	GPIO myGPIO(60, "out");
	for (int i = 0; i < 10; i++) {
		if (i % 2 == 0){
			myGPIO.setValue(1);
			std::cout << "LED ON" << std::endl;
		}
		else{
			myGPIO.setValue(0);
			std::cout << "LED OFF" << std::endl;
		}
	usleep(500000);
	}
	return 0;
}
