//*********Variable Declarations*********
 int trigpin=10;
 int echopin=11;
 long duration,startTime;
 int distance;

void setup() 
{
  Serial.begin(9600);
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
}

void loop() 
{
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);

  duration=pulseIn(echopin,HIGH);

  distance=duration*0.5*0.0343;
  Serial.print("distance(cm) is:"); 
  Serial.println(distance);

}
