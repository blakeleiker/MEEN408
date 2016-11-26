#include "PWM.h"

PWM::PWM(int PWMNumberr, int Periodd, int DutyCyclee) {
  // check that inputs are valid - for now we assume they are valid
  // Set internal port parameters
  PWMNumber = PWMNumberr;

  // Set filename strings
  std::stringstream ss;
  ss << "/sys/class/pwm/pwmchip0/pwm" << PWMNumber << "/";  // PWMFile
  PWMFile = ss.str();                                       //
  ss.clear();                                               //
  ss.str(std::string());                                    //
  ss << PWMFile << "period";                                // PeriodFile
  PWMPeriodFile = ss.str();                                 //
  ss.clear();                                               //
  ss.str(std::string());                                    //
  ss << PWMFile << "duty_cycle";                            // DutyCycleFile
  PWMDutyCycleFile = ss.str();                              //
  ss.clear();                                               //
  ss.str(std::string());                                    //
  ss << PWMFile << "polarity";                              // PolarityFile
  PWMPolarityFile = ss.str();                               //
  ss.clear();                                               //
  ss.str(std::string());                                    //
  ss << PWMFile << "enable";                                // EnableFile
  PWMEnableFile = ss.str();                                 //
  ss.clear();                                               //
  ss.str(std::string());                                    //

  // Export the PWM  Number (this will make the pwm directory we can then use)
  std::ofstream ofs;
  ofs.open(std::string("/sys/class/pwm/pwmchip0/export").c_str(),
           std::ios::app);
  if (!(ofs.is_open())) {
    std::cout << "Cannot export the PWM Pin\n";
    // throw exception;
  } else {
    ofs << PWMNumber;  // write pin number to export file
    ofs.close();       // and close the file
  }

  // Set Period and Duty Cycle
  setPeriod(Period);
  setDutyCycle(DutyCycle);
}

PWM::~PWM() {
  // Unexport the PWM
  setDutyCycle(0);
  std::ofstream ofs;
  ofs.open(std::string("/sys/class/pwm/pwmchip0/unexport").c_str(),
           std::ios::app);
  if (!(ofs.is_open())) {
    std::cout << "Cannot unexport the PWM Pin\n";
    // throw exception;
  } else {
    ofs << PWMNumber;  // write pin number to unexport file
    ofs.close();       // and close the file
  }
}

void PWM::setPeriod(int Periodd) {
  std::ofstream ofs;
  ofs.open(PWMPeriodFile.c_str(), std::ios::trunc);
  if (!(ofs.is_open())) {
    std::cout << "Cannot set the PWM Period.";
    // throw exception;
  } else {
    Period = Periodd;
    ofs << Periodd;
    ofs.close();
  }
}

void PWM::setDutyCycle(int DutyCyclee) {
  std::ofstream ofs;
  ofs.open(PWMDutyCycleFile.c_str(), std::ios::trunc);
  if (!(ofs.is_open())) {
    std::cout << "Cannot set the PWM Duty Cycle.";
    // throw exception;
  } else {
    DutyCycle = DutyCyclee;
    ofs << DutyCyclee;
    ofs.close();
  }
}

void PWM::setPolarity(std::string Polarityy) {
  std::ofstream ofs;
  ofs.open(PWMPolarityFile.c_str(), std::ios::trunc);
  if (!(ofs.is_open())) {
    std::cout << "Cannot set the PWM Polarity.";
    // throw exception;
  } else {
    Polarity = Polarityy;
    ofs << Polarityy;
    ofs.close();
  }
}
void PWM::enable(int enablee) {
  std::ofstream ofs;
  ofs.open(PWMEnableFile.c_str(), std::ios::trunc);
  if (!(ofs.is_open())) {
    std::cout << "Cannot enable the PWM.";
    // throw exception;
  } else {
    Enabled = enablee;
    ofs << enablee;
    ofs.close();
  }
}

int PWM::getPeriod() {
  std::ifstream ifs;
  int PeriodValue = 0;
  ifs.open(PWMPeriodFile.c_str(), std::ios::trunc);
  if (!(ifs.is_open())) {
    std::cout << "Cannot get the PWM Period.";
    // throw exception;
  } else {
    ifs >> PeriodValue;
    ifs.close();
  }
  return PeriodValue;
}

int PWM::getDutyCycle() {
  std::ifstream ifs;
  int DutyCycleValue;
  ifs.open(PWMDutyCycleFile.c_str(), std::ios::trunc);
  if (!(ifs.is_open())) {
    std::cout << "Cannot get the PWM Duty Cycle.";
    // throw exception;
  } else {
    ifs >> DutyCycleValue;
    ifs.close();
  }
  return DutyCycleValue;
}

std::string PWM::getPolarity() {
  std::ifstream ifs;
  std::string PolarityValue;
  ifs.open(PWMPolarityFile.c_str(), std::ios::trunc);
  if (!(ifs.is_open())) {
    std::cout << "Cannot get the PWM Polarity.";
    // throw exception;
  } else {
    ifs >> PolarityValue;
    ifs.close();
  }
  return PolarityValue;
}
