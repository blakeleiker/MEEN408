#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#define MAX 64
using namespace std;

int flashGPIOLED(int, int);

int main() {
  // readButton(117)
  flashGPIOLED(60, 5);
  return 0;
}

int flashGPIOLED(int GPIOPin, int times) {
  cout << "GPIO LED Flash Pin: " << GPIOPin << " start." << endl;

  // Create Strings that point to the GPIO Pin Value and Direction files
  FILE* LEDHandle = NULL;
  char setValue[4];
  char GPIOString[4];
  char GPIOValue[MAX];
  char GPIODirection[MAX];
  sprintf(GPIOString, "%d", GPIOPin);
  sprintf(GPIOValue, "/sys/class/gpio/gpio%d/value", GPIOPin);
  sprintf(GPIODirection, "/sys/class/gpio/gpio%d/direction", GPIOPin);

  // Export the Pin Number (this will make the Pin directory we can then use)
  // First we see if it is possible to create the directory. If not, quit.
  if ((LEDHandle = fopen("/sys/class/gpio/export", "ab")) ==
      NULL) {  // note that this opens the file
    printf("Cannot export the GPIO Pin");
    return 1;
  }
  // If the above works, export the pin:
  strcpy(setValue, GPIOString);                   // copy pin number to setValue
  fwrite(&setValue, sizeof(char), 2, LEDHandle);  // write set Value to
                                                  // LEDHANDLE
  fclose(LEDHandle);                              // and close the file

  // set pin direction
  if ((LEDHandle = fopen(GPIODirection, "rb+")) == NULL) {
    printf("Cannot open direction handle. \n");
    return 1;
  }
  strcpy(setValue, "out");
  fwrite(&setValue, sizeof(char), 3, LEDHandle);
  fclose(LEDHandle);

  // flash the led on the gpio pin
  for (int i = 0; i < times * 2; i++) {
    if ((LEDHandle = fopen(GPIOValue, "rb+")) == NULL) {
      printf("Cannot open value handle. \n");
      return 1;
    }
    cout << &LEDHandle << endl;  // this just prints out the file pointer value.
                                 // not sure why this is here
    if (i % 2 == 1) {
      strcpy(setValue, "0");
    } else {
      strcpy(setValue, "1");
    }
    fwrite(&setValue, sizeof(char), 1, LEDHandle);
    fclose(LEDHandle);
    sleep(1);
  }

  if ((LEDHandle = fopen("/sys/class/gpio/unexport", "ab")) == NULL) {
    printf("Cannot unexport GPIO Pin.\n");
    return 1;
  }
  strcpy(setValue, GPIOString);
  fwrite(&setValue, sizeof(char), 2, LEDHandle);
  fclose(LEDHandle);

  cout << "GPIO LED Flash PIN: " << GPIOPin << " end" << endl;
  return 0;
}
