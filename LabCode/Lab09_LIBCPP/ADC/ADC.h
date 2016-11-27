#ifndef ADC_H
#define ADC_H

#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class PWM {
 private:
  // ADC parameters
  int ADCVoltage;
  int ADCPinNumber;
  // filename strings
  std::string ADCDeviceFile;
  std::string ADCVoltageFile;

 public:
  ADC(int ADCPinNumberr);
  int readVoltage();
};

#endif
