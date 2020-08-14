#include <Servo.h>
#include <Wire.h>
#include "HCPCA9685.h"
#define  I2CAdd 0x40
HCPCA9685 HCPCA9685(I2CAdd);
int pos[4][14]; //first bracket= position of the motor; second= angle of corresp. motor  
void setup() 
{
  HCPCA9685.Init(SERVO_MODE);
  HCPCA9685.Sleep(false);
  Serial.begin(9600);
}
void trans(float p[], float q[])
{
  
  Serial.print("g ");
    float grad[14];
    int lasttime=millis(), currenttime=millis();
    for(int i=0;i<14;i++)
    {
      grad[i]=(q[i]-p[i])/10;
  Serial.print(q[i]);
  Serial.print(";");
  Serial.print(p[i]);
  Serial.print(";");
  Serial.print(grad[i]);
  Serial.print(";  "); 
  //Serial.println("i");
    }
    for(int j=0; j<=10; j++) 
    {
      for(int k=0;k<14;k++)
      {
        float b;
        b=map((p[k]+(grad[k]*j)), 0, 180, 10, 450);
        
          HCPCA9685.Servo(k,b);
          delay(7);
         
      Serial.print(p[k]+(grad[k]*j));
      Serial.print("  ");
      } 
      Serial.println();
      while((currenttime=millis()-lasttime)<=100)
      {
      }
      
      //Serial.println("j");
      lasttime=millis();
    }
  Serial.println("m");
}
void loop() 
{
  char c='0';
  if(Serial.available()>0)
  {
    c=Serial.read();
  }
  //float x[14]={80,80,30,50 ,90,85,145,130 ,0,0,0,0,0,0};
  float a[10][14]={{80+0 ,80+0 ,30+0 ,50+0 ,90+0 ,85+0 ,145+0 ,130+0  ,0,0,0,0,0,0}
                 ,{80+0 ,80+20,30+40,50+30 ,90+0 ,85-20,145-40,130-30 ,0,0,0,0,0,0}
                 ,{80-20,80+20,30+40,50+30 ,90-20,85-20,145-40,130-30 ,0,0,0,0,0,0}
                 ,{80-10,80+20,30+80,50+60 ,90-20,85-20,145-40,130-30 ,0,0,0,0,0,0}
                 ,{80-10,80+0 ,30+40,50+50 ,90-20,85-20,145-40,130-30 ,0,0,0,0,0,0}
                 ,{80+0 ,80+20,30+40,50+30 ,90-0 ,80-20,145-40,130-30 ,0,0,0,0,0,0}
                 ,{80+10,80+20,30+40,50+30 ,90+20,85-20,145-40,130-30 ,0,0,0,0,0,0}
                 ,{80+10,80+20,30+40,50+30 ,90+0 ,85+0 ,145+0 ,130+0  ,0,0,0,0,0,0}
                 ,{80+0 ,80+0 ,30+0 ,50+0  ,90+0 ,85+0 ,145+0 ,130+0  ,0,0,0,0,0,0}
                 ,{80+0 ,80+0 ,30+0 ,50+0  ,90+0 ,85+0 ,145+0 ,130+0  ,0,0,0,0,0,0}};
  
  if(c=='a')
  {
    for(int i=0;i<9;i++)
    {
      trans(a[i],a[i+1]);
    //Serial.println("dd");
    }
    //Serial.println("ddddd");
  }
  

}
