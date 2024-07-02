#include <Wire.h>
#include "bmp180.h"

BMPdata::BMPdata()
{
    oss = 0;
    temp = 0;
    pressure = 0;
}

////Reading calibration coefficients from the EEPROM
void BMPdata::readCalibrationData()
{
    Wire.beginTransmission(bmpAddress);
    Wire.write(regAdd);
    Wire.endTransmission();
    Wire.requestFrom(bmpAddress, 22);
    if (Wire.available() == 22)
    {
        ac1 = Wire.read()<<8 | Wire.read();
        delay(3);
        ac2 = Wire.read()<<8 | Wire.read();
        delay(3);
        // ac2 = -72; //uncomment on Proteus
        ac3 = Wire.read()<<8 | Wire.read();
        delay(3);
        ac4 = Wire.read()<<8 | Wire.read();
        delay(3);
        ac5 = Wire.read()<<8 | Wire.read();
        delay(3);
        ac6 = Wire.read()<<8 | Wire.read();
        delay(3);
        b1 = Wire.read()<<8 | Wire.read();
        delay(3);
        b2 = Wire.read()<<8 | Wire.read();
        delay(3);
        mb = Wire.read()<<8 | Wire.read();
        delay(3);
        mc = Wire.read()<<8 | Wire.read();
        delay(3);
        md = Wire.read()<<8 | Wire.read();
    }
    /*
    //To check the values
    Serial.println(ac1); Serial.println(ac2); Serial.println(ac3);
    Serial.println(ac4); Serial.println(ac5); Serial.println(ac6);
    Serial.println(b1); Serial.println(b2);
    Serial.println(mb); Serial.println(mc); Serial.println(md); 
    */
}

////To read the uncompensated temperature value
void BMPdata::readUncompTemp()
{
    Wire.beginTransmission(bmpAddress);
    Wire.write(controlReg);
    Wire.write(tempReg);
    Wire.endTransmission(bmpAddress);
    
    delayMicroseconds(4500);

    Wire.beginTransmission(bmpAddress);
    Wire.write(readMsbReg);
    Wire.endTransmission(bmpAddress);
    
    Wire.requestFrom(bmpAddress, 2);
    if (Wire.available() == 2)
    {
        ut = Wire.read()<<8; 
        uint8_t value = (uint8_t)(Wire.read()); 
        ut |= value; 
        /*
        //To check
        Serial.print("ut is: ");
        Serial.println(ut); 
        Serial.print("value temp is: ");
        Serial.println(value);
        */
    }
    else Serial.println("error with UT");
    
}

////To read the uncompensated pressure value
void BMPdata::readUncompPressure()
{
    Wire.beginTransmission(bmpAddress);
    Wire.write(controlReg);
    Wire.write(LowPressureReg + (oss << 6));
    Wire.endTransmission();
    delayMicroseconds(5000);

    Wire.beginTransmission(bmpAddress);
    Wire.write(readMsbReg);
    Wire.endTransmission();
    Wire.requestFrom(bmpAddress, 3);
    if (Wire.available() == 3)
    {   
        uint8_t value1 = Wire.read();
        uint8_t value2 = Wire.read();
        uint8_t value3 = Wire.read();
        
        // Combine the bytes in the correct order
        up = ((uint32_t)value1 << 16) | ((uint16_t)value2 << 8) | value3;
        up >>= (8 - oss);

        /* 
        //To check:
        Serial.println(value1); Serial.println(value2); Serial.println(value3);
        Serial.print("up: "); Serial.println(up);
        */
    }
    else Serial.println("error retrieving the UP value");
}

////To calculate the true temperature
void BMPdata::calcTrueTemp()
{
    x1 = (long)((ut - (int32_t)ac6) * ((int32_t)ac5) / pow(2, 15));
    x2 = ((int32_t)mc * pow(2, 11)) / ((x1 + (int32_t)md));
    b5 = (int32_t)(x1 + x2);
    temp = (long)(b5 + 8) / pow(2, 4);

    /*
    //To check
    Serial.print(ut); Serial.println(x1);
    Serial.println(x2); Serial.println(b5);
    */
}

////To calculate the true pressure
void BMPdata::calcTruePressure()
{
    b6 = b5 - 4000;
    x1 = (int32_t)((b2 * (b6 * b6 / pow(2, 12))) / pow(2, 11));
    x2 = ((int32_t)ac2 * b6 / pow(2, 11));
    x3 = x1 + x2;
    b3 = ((((int32_t)ac1 * 4 + x3) << oss) + 2) / 4;

    /*
    //To check
    Serial.println(b6);
    Serial.println(x1);
    Serial.println(x2);
    Serial.println(x3);
    Serial.println(b3);
    */

    x1 = ((int32_t)ac3 * b6) / pow(2, 13);
    x2 = ((int32_t)b1 * ((b6 * b6) / pow(2, 12))) / pow(2, 16);
    x3 = ((x1 + x2) + 2) / pow(2, 2);
    b4 = (uint32_t)ac4 * (unsigned long)(x3 + 32768) / pow(2, 15);
    b7 = ((unsigned long)up - b3) * (50000 >> oss);
    if (b7 < 0x80000000)
    {
        p = (unsigned long)((b7 * 2) / b4);
    }
    else
    {
        p = (unsigned long)((b7 / b4) * 2);
    }

    /*
    //To check
    Serial.println(x1); Serial.println(x2); Serial.println(x3);
    Serial.println(b4); Serial.println(b7); Serial.println(p);
    */

    x1 = (p / pow(2, 8)) * (p / pow(2, 8));
    //To check
    //Serial.println(x1);
    x1 = (x1 * 3038) / pow(2, 16);
    x2 = (-7357 * p) / pow(2, 16);
    p = (int32_t)(p + (x1 + x2 + (int32_t)3791) / pow(2, 4));
    pressure = p;

    /*
    //To check
    Serial.println(x1);
    Serial.println(x2);
    Serial.println(p);
    Serial.println(pressure);
    */

}

float BMPdata::getTemp()
{
    return temp;
}

int32_t BMPdata::getPressure()
{
    return pressure;
}
BMPdata::~BMPdata()
{

}



















