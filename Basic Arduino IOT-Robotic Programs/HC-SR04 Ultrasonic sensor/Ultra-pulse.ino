/*  This code is using standard function */

//*********Variable Declarations*********
int trigpin=10;
int echopin=11;
long duration,startTime;
int distance;
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);

}
signed long pulsein(int value)
{
  startTime=micros();
  while(digitalRead(echopin) == value) 
    { // wait if pin is already HIGH when the function is called, but timeout if it never goes LOW
        if (micros() - startTime > (23*1000)) 
        {
            return 0;
        }
    }
    startTime= micros();
    
    while(digitalRead(echopin) != value) 
    { // wait if pin is LOW when the function is called, but timeout if it never goes HIGH
        if (micros() - startTime > (23*1000)) 
        {
            return 0;
        }
    }
   startTime= micros();
    while (digitalRead(echopin) == value) 
    { // start timing the HIGH pulse width, but time out if over timeout
        if (micros() - startTime > (23*1000)) 
        {
            return 0;
        }
   }
return duration=micros()-startTime;
}
void loop() 
{
  
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  
  duration=pulsein(HIGH);
  distance=duration*0.5*0.0343;

  Serial.print("distance(cm) is:"); 
  Serial.println(distance);
}
