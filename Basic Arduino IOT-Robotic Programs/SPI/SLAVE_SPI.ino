#include<SPI.h>
boolean f=0;
byte recv;
void setup() 
{
  // put your setup code here, to run once:
SPI.begin();
pinMode(MISO,OUTPUT);
SPCR=(1<<SPE)|(1<<SPIE);
sei();
Serial.begin(9600);
}
ISR(SPI_STC_vect)
{recv=SPDR;
f=1;}

void loop() 
{
  // put your main code here, to run repeatedly:
Serial.println((char(recv)));
if(f)
{
SPDR='F';
} 
}
