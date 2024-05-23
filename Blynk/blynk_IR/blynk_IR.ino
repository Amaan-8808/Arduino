#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//*********Function initializations*********
void drive(char dir);

//**********Class definitions*********
//The Motor class is used to declare the pins being used for a Motor
//as well as drive the motors
class Motor{
  private:
    uint8_t pin1;
    uint8_t pin2;
  public:
    //Constructor for class
    Motor(uint8_t P1,uint8_t P2){
      pin1 = P1; //Assigns pin
      pin2 = P2; //Assigns pin
      pinMode(pin1, OUTPUT); //Sets pins to Output
      pinMode(pin2, OUTPUT);
      digitalWrite(pin1, LOW); //Ensures the motor does not start spinning randomly at the start
      digitalWrite(pin2, LOW);
    }
    void rotateClockwise(){
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, LOW);
    }
    void rotateAntiClockwise(){
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, HIGH);
    }
    void stopRotation(){
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
    } 
};

//The IR_Sensor class is used to declare the pins being used for a
//Sensor and get the output of the Sensor
class IR_Sensor{
  private:
    uint8_t pin;
    int lastSenseValue;
  public:
    //Constructor
    IR_Sensor(uint8_t P){
      pin = P;
      pinMode(pin, INPUT);
    }
    int sense(){
      lastSenseValue = digitalRead(pin);
      return lastSenseValue;
    }
};

//*********Variable Declarations*********
char auth[] = "";
char ssid[] = "";
char pass[] = "";


//*********Object Declarations***********
Motor M1(D5, D6);
Motor M2(D0, D1);
IR_Sensor S1(D2);
IR_Sensor S2(D3);

//*******Setup function to be executed once******
void setup()
{
  Serial.begin(9600);
  //Blynk.begin(auth, ssid, pass);
}

//******Loop function to be executed continuously*****
void loop()
{
  if(S1.sense() == 1 && S2.sense() == 0){
    drive('l');
  }
  else if(S2.sense() == 1 && S1.sense() == 0){
    drive('r');
  }
  else if(S1.sense() == 0 && S2.sense() == 0){
    drive('f');
  }
  else if(S1.sense() == 1 && S2.sense() == 1){
    drive('b');
  }
}

//Function to drive the two motors according to paramater passed into it
void drive(char dir){
  if(dir == 'f' || dir == 'F'){
    M1.rotateClockwise();
    M2.rotateClockwise();
    Serial.println("Forward");
  }
  else if(dir == 'b' || dir=='B'){
    M1.rotateAntiClockwise();
    M2.rotateAntiClockwise();
    Serial.println("Backward");
  }
  else if(dir == 'r' || dir == 'R'){
    M1.rotateClockwise();
    M2.rotateAntiClockwise();
    Serial.println("Right");
  }
  else if(dir == 'l' || dir == 'L'){
    M1.rotateAntiClockwise();
    M2.rotateClockwise();
    Serial.println("Left");
  }
  else{
    M1.stopRotation();
    M2.stopRotation();
    Serial.println("Stop");
  }
}

//Blynk Interrupt function for Virtual Pin 0
BLYNK_WRITE(V0){
  int x = param[0].asInt();
  int y = param[1].asInt();
  if (x>=5 && y<5 && y>-5){
    drive('b');
  }
  else if(x<=-5 && y<5 && y>-5){
    drive('f');
  }
  else if(y<=-5){
    drive('l');
  }
  else if(y>=5){
    drive('r');
  }
  else{
    drive('stop');
  }
  
 }
