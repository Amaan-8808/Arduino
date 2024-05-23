int led = 13;          
int brightness = 0;    
int fadeAmount = 5;    

// the setup routine runs once when you press reset:
void setup()
{
pinMode(led, OUTPUT);
}


void loop() {
 
analogWrite(led, brightness);
brightness = brightness + fadeAmount;
if (brightness <= 0 || brightness >= 255) 
{
    fadeAmount = -fadeAmount;
}
  
  delay(30);
}
