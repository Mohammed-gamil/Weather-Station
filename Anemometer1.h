#include <Arduino.h>


#ifndef ANEMOMETER1_H
#define ANEMOMETER1_H

class hall {
  private:
    char hallpin;
    int pulses;
  public:
    
    hall(char hallpin);
    
     void hall::init();
     int hall::CountingPulse();


};


class Anemometer {
 public:
  Anemometer(int);
  
   float Anemometer::AngVelocity(int pulses,float Time);
   
   float Anemometer::WindSpeed(float angV,float Arm);
  

};



#endif ANEMOMETER1_H