#ifndef Medochi_DHT11_h
#define Medochi_DHT11_h

#include "Arduino.h"

class DHT11
{
public:
  DHT11(int pin);
  int readHumidity();
  float readTemperature();

private:
  int _pin;

  int readRawData(byte data[5]);
  byte readByte();
  void startSignal();
};

#endif