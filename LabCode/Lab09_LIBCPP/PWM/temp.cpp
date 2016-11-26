#include <unistd.h>
#include <iostream>
#include <string>
#include "PWM.h"

int main() {
  PWM myPWM(0, 1000000, 0);
  sleep(2);
  return 0;
}
