

/*
 * Sequence try kar ab
Led on
Wait(yaha lockimg aayega)
Led off
Wait(yaha arrow drop hoga)
Motors
Release(yaha locking release hoga)
 */


#define encoder1PinA 2
#define encoder1PinB 3
#define PWM1 6 
#define Motor1Pin1 13 
#define Motor1Pin2 12 
#define Motor2Pin 11 // locking motor
#define PWM2 5
#define Button1 9
#define Button2 10
#define Button3 A5
//#define Button4 A4
//#define Button5 A3
#define Button6 A2
#define Button7 A1
//#define Piston  

int SetPoint1;
int PV1=0;
int err1=0;
double P1;
double kP1=0.4;
int output1;

void setup()
{
  Serial.begin(9600);
  pinMode(encoder1PinA, INPUT);
  pinMode(encoder1PinB, INPUT);
  pinMode(Motor1Pin1, OUTPUT);
  pinMode(Motor1Pin2, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(Button1,INPUT);
  pinMode(Button2, INPUT);
  pinMode(Button3, INPUT);
  attachInterrupt(0, doEncoder1A, RISING);
  //attachInterrupt(1, doEncoder2A, FALLING);
  
}

void loop()
{
                                         //Piston high
//if(digitalRead(Button4)==HIGH)
//{
// digitalWrite(Piston, HIGH);
//}
//  
  
                                        //locking function
if(digitalRead(Button6)==HIGH)
{
 digitalWrite(Motor2Pin, HIGH);
 analogWrite(PWM2, 255);
}

                                       //unlocking function
else if(digitalRead(Button7)==HIGH)
{
 digitalWrite(Motor2Pin, LOW);
 analogWrite(PWM2, 255);
} 
 else
 {
  analogWrite(PWM2, 0);
 }

if(digitalRead(Button3)==HIGH)                // STOP 
 {
    //analogWrite(PWM1, 0);
    stopit();
 }
 
if(digitalRead(Button2)==HIGH)                //up
  {
    digitalWrite(Motor1Pin1, LOW);
    digitalWrite(Motor1Pin2, HIGH);
    
    SetPoint1=2000;
    err1=SetPoint1-PV1;
    PID1(err1);
  } 
  
  
  else if(digitalRead(Button1)==HIGH)//down
  {
  
    //Serial.println("Works");
    digitalWrite(Motor1Pin1, HIGH);
    digitalWrite(Motor1Pin2, LOW);
    SetPoint1=0;
    err1= PV1-SetPoint1;
    PID1(err1);
    
  }
  
 
 
 
  //unlock
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

/*
void doEncoder2A() {
  
  if(digitalRead(encoder2PinA) == HIGH) 
  {
    if(digitalRead(encoder2PinB) == LOW) 
    {
      PV2 = PV2 - 1;         
    }
    else 
    {
      PV2 = PV2 + 1;         
    }
  }

  else   
  {
    if (digitalRead(encoder2PinB) == HIGH) 
    {
      PV2 = PV2 - 1;          
    }
    else 
    {
      PV2 = PV2 + 1;          
    }
  }
}
*/

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

 // up1();
  analogWrite(PWM1, output1); //0-255
  Serial.print(PV1);
  Serial.print("              ");
  Serial.print(output1);
  Serial.println("              ");

  
}

/*
void PID2()
{
     
  //err2=SetPoint2-PV2;
  
  P2=kP2*err2;
  out2=P2;
  output2=out2;
 /* if(output2<0)
 {
   output2=!out2;
 }
  if(output2>255)
  {
  output2=255;
  }
    if(output2<0)
  {
  output2=0;
  }
 // up2();
  analogWrite(PWM2, output2);
  Serial.print(PV2);
  Serial.print("              ");
  Serial.println(output2);
  
}

/*
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


void up2()
{
  digitalWrite(Motor2Pin1, LOW);
  digitalWrite(Motor2Pin2, HIGH);
}

void down2()
{
  digitalWrite(Motor2Pin1, HIGH);
  digitalWrite(Motor2Pin2, LOW);
}
*/

void stopit()
{
  digitalWrite(Motor1Pin1,LOW);
  digitalWrite(Motor1Pin2, LOW);
  analogWrite(PWM1,0);
}
