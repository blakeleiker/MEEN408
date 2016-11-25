#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
  cout << "ADC Start" << endl;
  FILE* ADCHandler = NULL;
  const char* ADCVoltage = "/sys/bus/iio/devices/iio:device0/in_voltage5_raw";
  char ADCVoltageRead[5] = {0};
  int Voltage;

  while (1) {
    if ((ADCHandler = fopen(ADCVoltage, "r")) != NULL) {
      fread(ADCVoltageRead, sizeof(char), sizeof(ADCVoltageRead - 1),
            ADCHandler);
      fclose(ADCHandler);
      stringstream ss(ADCVoltageRead);
      ss >> Voltage;
      cout << Voltage << endl;
      usleep(50000);
    }
  }
  cout << "ADC End" << endl;
  return 0;
}
