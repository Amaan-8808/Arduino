int pin=13;
int b=2;
boolean ledcur=false;
boolean prevbut=LOW;
void setup()
{
  pinMode(pin,INPUT);
  pinMode(b,OUTPUT);
}

void loop()
{
  if(digitalRead(b)==HIGH && prevbut==LOW)
  {
    ledcur=!ledcur;
  }
  else
  {
    digitalRead(pin);
  }
  digitalWrite(pin,ledcur);
}
