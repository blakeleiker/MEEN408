#include <unistd.h>
#include <iostream>
#include <string>
#include "PWM.h"

int main() {
  PWM myPWM(0, 1000000, 500000);
  // Initiate PWM
  std::cout << "PWM Start" << std::endl;
  myPWM.enable(1);

  // increase the duty cycle from 0% to 100% in 10 seconds smoothly
  double timeToFullLight = 10;  // seconds
  int numberOfIncrements = 1000;
  for (int i = 0; i < 10; i++) {
    std::cout << "count " << i << std::endl;
    myPWM.setDutyCycle(myPWM.getPeriod() * i / numberOfIncrements);
    usleep(int(timeToFullLight / numberOfIncrements * 1000000));
  }
  myPWM.enable(0);
  std::cout << "PWM End" << std::endl;
  return 0;
}
