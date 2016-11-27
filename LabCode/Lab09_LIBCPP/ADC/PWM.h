#ifndef ADC_H
#define ADC_H

#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class PWM {
 private:
  // PWM parameters
  int ADCVoltage;
  int ADCNumber
  std::string ADCVoltageFile
  int PWMNumber;
  std::string Polarity;
  int Enabled;
  // filename strings
  std::string PWMFile;
  std::string PWMPeriodFile;
  std::string PWMDutyCycleFile;
  std::string PWMPolarityFile;
  std::string PWMEnableFile;
  FILE* fileHandle;

 public:
  PWM(int PWMNumberr, int Periodd, int DutyCyclee);
  ~PWM();
  void setPeriod(int Periodd);
  void setDutyCycle(int DutyCyclee);
  void setPolarity(std::string Polarityy);
  void enable(int enablee);
  int getPeriod();
  int getDutyCycle();
  std::string getPolarity();
};

#endif
