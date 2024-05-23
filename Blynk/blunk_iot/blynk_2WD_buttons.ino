#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_DEVICE_NAME ""
#define BLYNK_AUTH_TOKEN "";

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define Motor1Pin1 D5
#define Motor1Pin2 D6
#define Motor2Pin1 D0
#define Motor2Pin2 D1

char auth[] = BLYNK_AUTH_TOKEN
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";
int v0_bS;

void setup()
{
  // Debug console
  Serial.begin(9600);
 
  Blynk.begin(auth, ssid, pass);
  
  pinMode(Motor1Pin1, OUTPUT);
  pinMode(Motor1Pin2, OUTPUT);
  pinMode(Motor2Pin1, OUTPUT);
  pinMode(Motor2Pin2, OUTPUT);

  digitalWrite(Motor1Pin1, LOW);
  digitalWrite(Motor1Pin2, LOW);
  digitalWrite(Motor2Pin1, LOW);
  digitalWrite(Motor2Pin2, LOW);
}

void loop()
{
  Blynk.run();
}

BLYNK_WRITE(1)
{
  int v1_bS=param.asInt();
  Serial.println(v1_bS);
  if(v1_bS==1)
   {
     drive('f'); 
     
   } 
}

BLYNK_WRITE(0)
{
  int v0_bS=param.asInt();
  if(v0_bS==1)
   {
     drive('b'); 
   } 
} 
void drive(char dir)
{  
  if(dir == 'f')
  {
    digitalWrite(Motor1Pin1, HIGH);
    digitalWrite(Motor1Pin2, LOW);
    digitalWrite(Motor2Pin1, HIGH);
    digitalWrite(Motor2Pin2, LOW);
    Serial.println("Forward");
  }
  else if(dir == 'b' )
  {
    digitalWrite(Motor1Pin1, LOW);
    digitalWrite(Motor1Pin2, HIGH);
    digitalWrite(Motor2Pin1, LOW);
    digitalWrite(Motor2Pin2, HIGH);
    Serial.println("Backward");
  }

  else
  {
    digitalWrite(Motor1Pin1, LOW);
    digitalWrite(Motor1Pin2, LOW);
    digitalWrite(Motor2Pin1, LOW);
    digitalWrite(Motor2Pin2, LOW);
    Serial.println("Stop");
  } }
