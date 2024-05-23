#include "Wire.h"
#include <MPU6050_light.h>
#define Motor1Pin1 8 
#define Motor1Pin2 9
#define PWM1 5
MPU6050 mpu(Wire);
unsigned long timer = 0;
int kp=19.5,kd,ki,p=0;
int err_g=0,perr_g=0,d,i,currangle,output,angX,angY,angZ;
void setup() 
{
  Serial.begin(9600);
  Wire.begin();
  pinMode(Motor1Pin1,OUTPUT);
  pinMode(Motor1Pin2,OUTPUT);

  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
}

void loop() {
  mpu.update();
  angX=mpu.getAngleX();
  angY=mpu.getAngleY();
  angZ=mpu.getAngleZ();
  Serial.print("X : ");
	Serial.print(angX);
	Serial.print("\tY : ");
	Serial.print(angY);
	Serial.print("\tZ : ");
	Serial.println(angZ);
  gyro_pid(55);
  Serial.print("output:");
  Serial.println(output);
  delay(250);
}

void gyro_pid(int setangle)
{ 
  currangle=mpu.getAngleX();
  err_g=setangle-currangle;
  //Serial.println(err_g);
  p=kp*err_g;
  d=kd*(err_g-perr_g);
  i=ki*err_g+i;
  perr_g=err_g;
  output=p+d+i;
  if(output>255)
  output=255;
  if(output>0)
  { 
   digitalWrite(Motor1Pin1, HIGH);
   digitalWrite(Motor1Pin2, LOW);
   analogWrite(PWM1, output);
  }
  if(output<0)
  { 
   digitalWrite(Motor1Pin1, LOW);
   digitalWrite(Motor1Pin2, HIGH);
   analogWrite(PWM1, output);
  }
}
