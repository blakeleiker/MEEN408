#include "GPIO.h"

GPIO::GPIO(int gpioPinNumberr, std::string directionn) {
  // check that inputs are valid
  if (!(directionn.compare("out") || directionn.compare("in"))) {
    printf("Invalid Direction Input. \n");
    //throw exception;
  }
  // Set internal port parameters
  gpioPinNumber = gpioPinNumberr;
  direction = directionn;
  // Set file strings
  std::stringstream ss;
  // Pin Number String
  ss << gpioPinNumber;
  GPIOFile = ss.str();
  ss.clear();
  ss.str(std::string());
  // Value File String
  ss << "/sys/class/gpio/gpio" << gpioPinNumber << "/value";
  GPIOValueFile = ss.str();
  ss.clear();
  ss.str(std::string());
  // Direction File String
  ss << "/sys/class/gpio/gpio" << gpioPinNumber << "/direction";
  GPIODirectionFile = ss.str();
  ss.clear();
  ss.str(std::string());

  // Export the Pin Number (this will make the Pin directory we can then use)
  // First we see if it is possible to create the directory. If not, quit.
  std::ofstream ofs;
  ofs.open(std::string("/sys/class/gpio/export").c_str(), std::ios::app);
  if (!(ofs.is_open())) {
    std::cout << "Cannot export the GPIO Pin\n";
    //throw exception;
  }
  else{
    // If connecting to the export file works, we export the pin number.
    ofs << gpioPinNumber;  // write pin number to export file
    ofs.close();           // and close the file
  }

  // Set the pin direction
  ofs.open(GPIODirectionFile.c_str(), std::ios::trunc);
  if (!(ofs.is_open())) {
    std::cout << "Cannot set the GPIO direction.";
    //throw exception;
  }
  else{
    // If connecting to the direction file works, we export the direction
    ofs << direction;
    ofs.close();     
  }
}

GPIO::~GPIO()
{
  std::ofstream ofs;
  ofs.open(std::string("/sys/class/gpio/unexport").c_str(), std::ios::app);
  if (!(ofs.is_open())) {
    std::cout << "Cannot unexport the GPIO Pin\n";
    //throw exception;
  }
  else{
    // If connecting to the export file works, we export the pin number.
    ofs << gpioPinNumber;  // write pin number to export file
    ofs.close();           // and close the file
  }

	
}
void GPIO::setValue(int valuee)
{
  std::ofstream ofs;
  ofs.open(GPIOValueFile.c_str(), std::ios::trunc);
  if (!(ofs.is_open())) {
    std::cout << "Cannot set the GPIO Value.";
    //throw exception;
  }
  else{
    ofs << valuee;
    ofs.close();     
  }
}

int GPIO::getValue()
{
  std::ifstream ifs;
  int value = 0;
  ifs.open(GPIOValueFile.c_str());
  if (!(ifs.is_open())) {
    std::cout << "Cannot get the GPIO Value.";
    //throw exception;
  }
  else{
    ifs >> value;
    ifs.close();     
  }
  return value;
}


