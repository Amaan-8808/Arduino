#define encoder1PinA 2
#define encoder1PinB 3
#define PWM2 5
#define Motor1Pin1 8 
#define Motor2Pin 6 // locking motor
#define PWM1 9
#define Piston 10
#define stop_time 700

int times=0;
int SetPoint1;
int PV1=0;
int err1=0;
double P1;
double kP1=1.1;
int output1;
int t1;
int flag_stop;
int flag2=0;

void setup()
{
  Serial.begin(115200);
  pinMode(encoder1PinA, INPUT);
  pinMode(encoder1PinB, INPUT);
  pinMode(Motor1Pin1, OUTPUT);
 // pinMode(Motor1Pin2, OUTPUT);
  pinMode(PWM1, OUTPUT);
  attachInterrupt(0, doEncoder1A, RISING);

}

void loop()
{
  if (Serial.available())
  { 
  int t = 2;
  t = Serial.read();
  Serial.print("t:");
  Serial.println(t);  
   //locking function
  if(t == 53 && flag_stop==0)
  {
    Serial.println("Locking working");
    t1=millis();
    //Serial.println(millis());
    digitalWrite(Motor2Pin, HIGH);
  
    analogWrite(PWM2, 200);
    while(( times = millis() - t1) < stop_time){
      Serial.println(times);
    }
    flag_stop = 1;
    
    analogWrite(PWM2, 0);
    Serial.println("Piston Low working");
    digitalWrite(Piston, LOW);
    
    
 
  }

 //unlocking function
  if(t == 73 && flag_stop==1)
  {
    Serial.println("Unlocking Working");
    t1=millis();
    int times;
    //Serial.println(t1);
    digitalWrite(Motor2Pin, LOW);
    analogWrite(PWM2, 200);
    while(( times = millis() - t1) < stop_time){
      Serial.println(times);
    }
    flag_stop = 0;
    analogWrite(PWM2, 0);
  } 
 

  
  if(t == 3)
  {
    stopit();
  }
 
  if(t == 13 && flag2==0) //up
  {

    digitalWrite(Motor1Pin1, LOW);
    SetPoint1=2500;
    err1=SetPoint1-PV1;
    PID1(err1);
    while(PWM1!=0)
    {
      flag2=1;
      //unlocking
      t1=millis();
      digitalWrite(Motor2Pin, LOW);
      analogWrite(PWM2, 200);
      while(( times = millis() - t1) < stop_time);
      analogWrite(PWM2, 0);
      
    }
  } 
  
  
  if(t == 23)//down
  {
    //Serial.println(t);
    //Serial.println("Works");

    digitalWrite(Motor1Pin1, HIGH);
    SetPoint1=0;
    err1= PV1-SetPoint1;
    PID1(err1);
  }
  
  if(t ==  43)
  {
    Serial.println("Piston High working");
    digitalWrite(Piston, HIGH);
  }
  if(t == 63)
  {
    Serial.println("Piston Low working");
    digitalWrite(Piston, LOW);
  }
 
   //PID1();
    
 
  //unlock
  }
}

void doEncoder1A() 
{
  if(digitalRead(encoder1PinA) == HIGH) 
  {
    if(digitalRead(encoder1PinB) == LOW) 
    {
      PV1 = PV1 + 1;         
    }
    else 
    {
      PV1 = PV1 - 1;         
    }
   }
   else   
  {
    if(digitalRead(encoder1PinB) == HIGH) 
    {
      PV1 = PV1 + 1;          
    }
    else 
    {
      PV1 = PV1 - 1;          
    }
  }
}

void PID1(int err)
{
    
  //int perr=err1;
  //err1=SetPoint1-PV1;
  
  P1=kP1*err;
  //D1=kD1*(perr-err1);
  output1=P1;
 /*if(output1<0)
 {
   output1=!out1;
 }*/
  if(output1>255)
  {
    output1=255;
  }
  if(output1<0)
  {
    output1=0;
  } 

 //up1();
  analogWrite(PWM1, output1); //0-255
  Serial.print(PV1);
  Serial.print("              ");
  Serial.print(output1);
  Serial.println("              ");

  
}
//void up1()
//{
//  digitalWrite(Motor1Pin1, HIGH);
//  digitalWrite(Motor1Pin2, LOW);
//}
//
//void down1()
//{
//  digitalWrite(Motor1Pin1, LOW);
//  digitalWrite(Motor1Pin2, HIGH);
//}

void stopit()
{
  digitalWrite(Motor1Pin1,LOW);
  analogWrite(PWM2,0);
  analogWrite(PWM1,0);
}
