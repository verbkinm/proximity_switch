const int ledPin =  13;
char ledState = LOW;

const int proximitySwitch = 8;

const int relePin =  18;
char releState = LOW;

bool powerOn = false;
bool input = false;
//==========START==========
//void(* resetFunc) (void) = 0;
void powerShift(int _delay = 10)
{
  powerOn = !powerOn;
  if(powerOn){
    ledState = LOW;
    releState= HIGH;  
  }
  else{
    ledState = HIGH;
    releState= LOW;
  }
  digitalWrite(ledPin, ledState);
  digitalWrite(relePin,releState);
    
  delay(_delay);
}
void setup()
{
  Serial.begin(9600); 						// start the serial port
  
  pinMode(ledPin,  OUTPUT);
  pinMode(relePin, OUTPUT);
  pinMode(proximitySwitch, INPUT);

  pinMode(10, OUTPUT); 
  
  for(int i = 0; i < 19; i++){
    ledState = !ledState;
    digitalWrite(ledPin, ledState); 
    delay(50);
  }
  
  digitalWrite(relePin,releState);
}
void loop()
{
  input = !digitalRead(proximitySwitch);
  if(input){
    powerShift();
    int buffState = ledState;
    while(!digitalRead(proximitySwitch)){
      digitalWrite(ledPin, !buffState);
      delay(100);
      digitalWrite(ledPin, buffState); 
      delay(100);
    }
    digitalWrite(ledPin, ledState);
  }
}
