
#include "Anemometer1.h"
#include <TimerOne.h>
#define HallPin A0
float Time=60;  //Time in seconds [sec]
float Radius=0.15 ; //radius in meters [m]
int   PulseNum;
float V_angular;    //angular velocity [Rad/sec]
float V_wind;      //wind velocity [m/sec]
float V_wind2;
 hall Hall(HallPin);  //An object for the hall class
 Anemometer  Ane(2);  //An object for the Anemometer class



void setup() {
 pinMode(A2,INPUT);
  // put your setup code here, to run once:
  Timer1.initialize(Time*10000000);
  Timer1.attachInterrupt(CalV );  
  Hall.init();
  Serial.begin(9600);

}
 
void loop() {

//Serial.println(analogRead(A2));

PulseNum=Hall.CountingPulse() ;

// Serial.print("Hello");
// Serial.println(PulseNum);
}
 
void CalV(){                       //The function that will be executed when the interrupt occurs 

  V_angular=Ane.AngVelocity(PulseNum,Time);
  V_wind=Ane.WindSpeed(V_angular,Radius);

  Serial.print("Wind Speed = ");
 Serial.println(V_wind);
 Hall.pulses=0;
   

}


