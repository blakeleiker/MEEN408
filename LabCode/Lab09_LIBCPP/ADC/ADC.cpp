#include "ADC.h"

ADC::ADC(int ADCPinNumberr) {
  // check that inputs are valid - for now we assume they are valid
  // Set internal port parameters
  ADCPinNumber = ADCPinNumberr;

  // Set filename strings
  std::stringstream ss;
  ss << "/sys/bus/iio/devices/iio:device0/";  // ADCDeviceFile
  ADCDeviceFile = ss.str();                   //
  ss.clear();                                 //
  ss.str(std::string());                      //
  ss << ADCDeviceFile << "in_voltage" << ADCPinNumber
     << "_raw";               // ADCVoltageFile
  ADCVoltageFile = ss.str();  //
  ss.clear();                 //
  ss.str(std::string());      //
}

int ADC::readVoltage() {
  double maxADCVoltage = 1.8;  // maximum allowed voltage -- DO NOTE EXCEED
  double minADCVoltage = 0;    // minimum measureable voltage (lowest output)
  int maxRaw = 4095;           // maximum output from ADC
  int minRaw = 0;              // minimum output from ADC
  std::ifstream ifs;

  int rawADC = 0;
  ifs.open(ADCVoltageFile.c_str());
  if (!(ifs.is_open())) {
    std::cout << "Cannot get the ADC Voltage.\n";
    // throw exception;
  } else {
    ifs >> rawADC;
  }
  ifs.close();
  double ADCVoltage =
      ((maxADCVoltage - minADCVoltage) / (maxRaw - minRaw)) * rawADC +
      minADCVoltage;
  return ADCVoltage;
}
