#include<iostream>
#include "EQEP.h"

int main()
{
	EQEP myEQEP(0);
	std::cout << "EQEP Start" << std::endl;
	for (int i = 0; i < 30; i++){
		std::cout << "(Angle) : (" << myEQEP.readPosition() << ")" << std::endl;
	}
	std::cout << "EQEP End" << std::endl;
	return 0;
}
