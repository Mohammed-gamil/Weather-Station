#include "bmp180.h"
long temp;
long pressure;
BMPdata bmp; // = new BMPdata() ;

void setup() {
  
  Serial.begin(9600); //Initializing with 9600 baud rate
  Wire.begin(); //Initializing I2C communication
  Serial.println(" ");
  Serial.println("******************REBOOT***********************");
  
}

void loop() {
  bmp.readCalibrationData();
  bmp.readUncompTemp();
  bmp.readUncompPressure();
  bmp.calcTrueTemp();
  bmp.calcTruePressure();  

  temp = bmp.getTemp();
  pressure = bmp.getPressure();
  
  Serial.println("");
  Serial.print("The temperature is: ");
  Serial.print(temp / 10.0);
  Serial.println(" degC");
  Serial.print("The pressure is: ");
  Serial.print(pressure / 100.0);
  Serial.println(" hPa.");

  delay(5000);
}
