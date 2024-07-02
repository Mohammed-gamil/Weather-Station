#ifndef BMP180_h
#define BMP180_h

#include <Arduino.h>
#include <Wire.h>

#define bmpAddress 0x77
#define regAdd 0xAA
#define controlReg 0xF4
#define tempReg 0x2E
#define LowPressureReg 0x34
#define readMsbReg 0xF6

class BMPdata {
private:
    char oss;
    int32_t temp;
    int32_t pressure;
    int16_t ac1, ac2, ac3, b1, b2, mb, mc, md;
    uint16_t ac4, ac5, ac6;
    long x1, x2, x3, b3, b5, b6, p;
    uint16_t ut; 
    uint32_t up; 
    unsigned long b4, b7;
    

public:
    BMPdata();
    void readCalibrationData();
    void readUncompTemp();
    void readUncompPressure();
    void calcTrueTemp();
    void calcTruePressure();
    float getTemp(); //getter function
    int32_t getPressure(); //getter function
    ~BMPdata();
};


#endif
