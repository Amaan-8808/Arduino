#define encoderPinA 2
#define encoderPinB 3
#define PWM1 6
#define Motor1Pin1 12
#define Motor1Pin2 13
#define PWM2
#define Motor2Pin1
#define Motor2Pin2
#define button1 9
#define button2 10
#define button3 A5
//#define button4 A4
//#define button5 A3
//#define button6 A2
//#define button7 A1
//#define piston

int SetPoint;
int PV=0;
int err=0;
double P;
double kP=0.30;
int output;




void setup() 
{
  Serial.begin(9600);
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  pinMode(Motor1Pin1, OUTPUT);
  pinMode(Motor1Pin2, OUTPUT);
  pinMode(PWM1, OUTPUT);
//pinMode(Motor2Pin1, OUTPUT);
//pinMode(Motor2Pin2, OUTPUT);
//pinMode(PWM2, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
//pinMode(button4, INPUT);
//pinMode(button5, INPUT);
//pinMode(button6, INPUT);
//pinMode(button7, INPUT);
  attachInterrupt(0, doEncoderA, RISING);

}

void loop() {

  //up
  if(digitalRead(button1) ==HIGH)
  {
    digitalWrite(Motor1Pin1, HIGH);
    digitalWrite(Motor1Pin2, LOW);
    SetPoint=2300;
    err=SetPoint-PV;
    PID();
  }
  

  //down
  if(digitalRead(button2) ==HIGH)
  {
    digitalWrite(Motor1Pin1, LOW);
    digitalWrite(Motor1Pin2, HIGH);
    SetPoint=0;
    err=PV-SetPoint;
    PID();
  }
if(digitalRead(button3)==HIGH)
  {
    stopit();
  }
 
 

}

void doEncoderA() 
{
  if(digitalRead(encoderPinA) == HIGH) 
  {
    if(digitalRead(encoderPinB) == LOW) 
    {
      PV = PV - 1;         
    }
    else 
    {
      PV = PV + 1;         
    }
   }
   else   
  {
    if(digitalRead(encoderPinB) == HIGH) 
    {
      PV = PV - 1;          
    }
    else 
    {
      PV = PV + 1;          
    }
  }
}

void PID()
{
  P=kP*err;
  output=P;
  if(output>255)
  {
    output=255;
  }
  if(output<0)
  {
    output=0;
  } 
  analogWrite(PWM1, output); //0-255
  Serial.print(PV);
  Serial.print("              ");
  Serial.print(output);
  Serial.println("              ");
}

void stopit()
{
  digitalWrite(Motor1Pin1,LOW);
  digitalWrite(Motor1Pin2, LOW);
  analogWrite(PWM1,0);
}
