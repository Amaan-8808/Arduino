#define apin 2
#define bpin 3
int curastate;
int prevastate;
int counter;
void setup() 
{
  // put your setup code here, to run once:
pinMode(apin,INPUT);
pinMode(bpin,INPUT);
Serial.begin(9600);
prevastate=digitalRead(apin);
attachInterrupt(digitalPinToInterrupt(apin),position,CHANGE);
}

void loop() 
{

Serial.println(position());
}
int position()
{
curastate=digitalRead(apin);
if(curastate!=prevastate)
{
  if(digitalRead(bpin)!=curastate)
     {counter--;}
     else
      {counter++;}
prevastate=curastate;
}}
