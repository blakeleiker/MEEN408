#include <unistd.h>
#include <iostream>
#include <string>
#include "PWM.h"

int main() {
  PWM myPWM(0, 1000000, 500000);
  sleep(2);
  myPWM.enable(1);
  sleep(2);
  myPWM.enable(0);
  return 0;
}
