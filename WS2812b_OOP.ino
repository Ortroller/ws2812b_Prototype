#include "Led_obj.h"

uint8_t HSVpower[90] = 
{
200,0,30  , 180, 0, 70 , 110, 0, 100, /* 4 leds por linha*/
70,0,120 , 40,0,160  , 0,0,200,
0,0,240  , 0,0,250   , 0,40, 210,
0,80,170 , 0,120,130 , 0,160,100,
0,200,60 , 0,220,20 ,
0,250,0  , 0,250,0, 0,250,0  ,
0,250,0  , 30,230,0, 60,210,0, 
80,170,0 , 110,140,0 , 140,110,0,
170,90,0 , 190, 70,0, 220,50,0 , 
240,30,0 , 250, 10,0, 250,0,0  , 250,0,0
};



void setup() {
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  Serial.begin(9600);

  Led_obj stripe (5, 30);
  stripe.PalEffect(0, HSVpower, 90);
  while(true){
    stripe.rotate();
  }
}




void loop() {
}
