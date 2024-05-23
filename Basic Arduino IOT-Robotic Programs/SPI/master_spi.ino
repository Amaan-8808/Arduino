#include<SPI.h>
int sspin=10;
void setup() 
{
  // put your setup code here, to run once:
SPI.begin();
pinMode(sspin,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(sspin,LOW);
delay(1000);
char test=SPI.transfer(65);
digitalWrite(sspin,HIGH);
Serial.println("test");
 
}
