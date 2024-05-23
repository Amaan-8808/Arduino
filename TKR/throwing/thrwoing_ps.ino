

#define encoder1PinA 2
#define encoder1PinB 3
#define PWM1 6 
#define Motor1Pin1 12 
#define Motor1Pin2 13 
#define Motor2Pin 11 // locking motor
#define PWM2 5
#define Piston 7

int SetPoint1;
int PV1=0;
int err1=0;
double P1;
double kP1=0.48;
int output1;

void setup()
{
  Serial.begin(115200);
  pinMode(encoder1PinA, INPUT);
  pinMode(encoder1PinB, INPUT);
  pinMode(Motor1Pin1, OUTPUT);
  pinMode(Motor1Pin2, OUTPUT);
  pinMode(PWM1, OUTPUT);
  attachInterrupt(0, doEncoder1A, RISING);
}

void loop()
{
  if (Serial.available())
  { 
  //locking function

  int t = 2;
  t = Serial.read();
    
  if(t == 53)
  {
    Serial.println("Locking working");
    digitalWrite(Motor2Pin, HIGH);
    analogWrite(PWM2, 255);
  }

 //unlocking function
  else if(t == 73)
  {
    Serial.println("Unlocking Working");
    digitalWrite(Motor2Pin, LOW);
    analogWrite(PWM2, 255);
  } 
 else
 {
  analogWrite(PWM2, 0);
 }

  
  if(t == 3)
  {
    stopit();
  }
 
  if(t == 13) //up
  {
    digitalWrite(Motor1Pin1, LOW);
    digitalWrite(Motor1Pin2, HIGH);
    
    SetPoint1=3250;
    err1=SetPoint1-PV1;
  } 
  
  
  if(t == 23)//down
  {
    Serial.println(t);
    //Serial.println("Works");
    digitalWrite(Motor1Pin1, HIGH);
    digitalWrite(Motor1Pin2, LOW);
    SetPoint1=0;
    err1= PV1-SetPoint1;
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
 
    PID1();
    
 
  //unlock
  }
}

void doEncoder1A() 
{
  if(digitalRead(encoder1PinA) == HIGH) 
  {
    if(digitalRead(encoder1PinB) == LOW) 
    {
      PV1 = PV1 - 1;         
    }
    else 
    {
      PV1 = PV1 + 1;         
    }
   }
   else   
  {
    if(digitalRead(encoder1PinB) == HIGH) 
    {
      PV1 = PV1 - 1;          
    }
    else 
    {
      PV1 = PV1 + 1;          
    }
  }
}

void PID1()
{
    
  //int perr=err1;
  //err1=SetPoint1-PV1;
  
  P1=kP1*err1;
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
void up1()
{
  digitalWrite(Motor1Pin1, HIGH);
  digitalWrite(Motor1Pin2, LOW);
}

void down1()
{
  digitalWrite(Motor1Pin1, LOW);
  digitalWrite(Motor1Pin2, HIGH);
}

void stopit()
{
  digitalWrite(Motor1Pin1,LOW);
  digitalWrite(Motor1Pin2, LOW);
  analogWrite(PWM1,0);
}
