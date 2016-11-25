#include <stdio.h>
#include <unistd.h>
#include <iostream>
using namespace std;

#define PERIOD 1000000

int main() {
  cout << "PWM Start" << endl;

  FILE* PWMHandle = NULL;
  const char* PWMPeriod = "/sys/class/pwm/pwmchip0/pwm0/period";
  const char* PWMDutyCycle = "/sys/class/pwm/pwmchip0/pwm0/duty_cycle";
  const char* PWMEnable = "/sys/class/pwm/pwmchip0/pwm0/enable";
  char setValue[10];

  // Set PWM period, duty cycle, and enabled status
  if ((PWMHandle = fopen(PWMPeriod, "r+")) != NULL) {
    fwrite("1000000", sizeof(char), 7, PWMHandle);
    fclose(PWMHandle);
  }
  if ((PWMHandle = fopen(PWMDutyCycle, "r+")) != NULL) {
    fwrite("0", sizeof(char), 1, PWMHandle);
    fclose(PWMHandle);
    // cout << "DutyCycle " << sizeof(PERIOD/2)/sizeof(char) << endl;
  }
  if ((PWMHandle = fopen(PWMEnable, "r+")) != NULL) {
    fwrite("1", sizeof(char), 1, PWMHandle);
    fclose(PWMHandle);
  }

  // increase the duty cycle from 0% to
  for (int i = 0; i < 10; i++) {
    cout << "count " << i << endl;
    sprintf(setValue, "%d", int(PERIOD * i / 10));
    if ((PWMHandle = fopen(PWMDutyCycle, "r+")) != NULL) {
      fwrite(setValue, sizeof(char), sizeof(setValue), PWMHandle);
      fclose(PWMHandle);
    }
    sleep(1);
  }

  // reset duty cycle to 0 and disable
  if ((PWMHandle = fopen(PWMDutyCycle, "r+")) != NULL) {
    fwrite("0", sizeof(char), 1, PWMHandle);
    fclose(PWMHandle);
    // cout << "DutyCycle " << sizeof(PERIOD/2)/sizeof(char) << endl;
  }
  if ((PWMHandle = fopen(PWMEnable, "r+")) != NULL) {
    fwrite("0", sizeof(char), 1, PWMHandle);
    fclose(PWMHandle);
  }

  cout << "PWM End" << endl;
  return 0;
}
