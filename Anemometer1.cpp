#include "Anemometer1.h"
int pulses;
    
  char hallpin;
  hall::hall(char hallpin){  
      this->hallpin=hallpin; 
      
    }
  void hall::init(){
    pinMode(hallpin,INPUT);

   }
    
  int hall::CountingPulse(){                  //This function calculates the number of revolutions
                                          
     int hallval=analogRead(hallpin);
       
       if (hallval<500){
            
             pulses++;

       }

        return pulses;
       
       
   }
    


 
  Anemometer::Anemometer(int){}
  float Anemometer::AngVelocity(int pulses,float Time){
      float const  pi=3.14;
      return (pulses*2*pi)/Time;    //This function takes the number of pulses(revolutions) & returns angular velocity [rad/sec]
  
     }
     float Anemometer::WindSpeed(float angV,float Arm){
      return angV*Arm;       //This function returns the linear velocity in [m/s]
        
     }                       
 
  


