#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
  cout << "QuadratureEncoder Start" << endl;
  FILE* QuadHandler = NULL;
  const char* QuadPositionFile = "/sys/devices/platform/ocp/48304000.epwmss/48304200.ehrpwm/position";
  char QuadPositionRead[5] = {0};
  int QuadPosition;

  while (1) {
    if ((QuadHandler = fopen(QuadPositionFile, "r")) != NULL) {
      fread(QuadPositionRead, sizeof(char), sizeof(QuadPositionRead - 1),
            QuadHandler);
      fclose(QuadHandler);
      stringstream ss(QuadPositionRead);
      ss >> QuadPosition;
      cout << QuadPosition << endl;
      usleep(50000);
    }
  }
  cout << "QuadratureEncoder End" << endl;
  return 0;
}
