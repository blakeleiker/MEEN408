#include<iostream>
#include "ADC.h"

int main()
{
	ADC myADC(5);
	std::cout << "ADC Start" << std::endl;
	for (int i = 0; i < 30; i++){
		std::cout << "(Voltage, Raw) : (" << myADC.readVoltage() << ", " <<  myADC.readRaw() << ")" << std::endl;
	}
	std::cout << "ADC Emd" << std::endl;
	return 0;
}
