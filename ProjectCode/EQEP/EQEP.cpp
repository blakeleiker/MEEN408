#include "EQEP.h"

EQEP::EQEP(int EQEPNumberr) {
  // check that inputs are valid - for now we assume they are valid
  // Set internal port parameters
  EQEPNumber = EQEPNumberr;

  // Set filename strings
  std::stringstream ss;
  ss << "/sys/devices/platform/ocp/48304000.epwmss/48304180.eqep/";  // DeviceFile
  EQEPDeviceFile = ss.str();                   //
  ss.clear();                                 //
  ss.str(std::string());                      //
  ss << EQEPDeviceFile << "position";  // PositionFile
  EQEPPositionFile = ss.str();  //
  ss.clear();                 //
  ss.str(std::string());      //
}

int EQEP::readPosition() {
  std::ifstream ifs;
  ifs.open(EQEPPositionFile.c_str());
  if (!(ifs.is_open())) {
    std::cout << "Cannot get the EQEP Position.\n";
    // throw exception;
  } else {
    ifs >> EQEPPosition;
  }
  ifs.close();
  return EQEPPosition;
}
