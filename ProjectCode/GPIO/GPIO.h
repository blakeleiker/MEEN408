#ifndef GPIO_H
#define GPIO_H

#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class GPIO {
 private:
  // port parameters
  int gpioPinNumber;
  std::string direction;
  int value;
  // filename strings
  std::string GPIOFile;
  std::string GPIOValueFile;
  std::string GPIODirectionFile;
  FILE* fileHandle;

 public:
  GPIO(int gpioPinNumberr, std::string directionn);
  ~GPIO();
  void setValue(int Valuee);
  int getValue();
};

#endif
