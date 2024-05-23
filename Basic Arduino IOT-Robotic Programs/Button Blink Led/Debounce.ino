
int b = 2;  
int lp = 13;      

int ledState = HIGH;         
int bcur;            
int prevb = LOW;   
unsigned long lastDebounceTime = 0;  

unsigned long debounceDelay = 50;    


void setup() {
  pinMode(b, INPUT);
  pinMode(lp, OUTPUT);

  
  digitalWrite(lp, ledState);
}

void loop() {
  
  int reading = digitalRead(b);


  if (reading != prevb) {
   
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) 
  {
     if (reading != bcur) {
     bcur = reading;

    
      if (bcur == HIGH) {
        ledState = !ledState;
      }
    }
  }

  
  digitalWrite(lp, ledState);


  prevb = reading;
}
