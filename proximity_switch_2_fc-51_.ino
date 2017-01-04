const int ledPin =  13;
int ledState = LOW;

const int proximitySwitch = 8;

const int relePin =  18;
int releState = LOW;

int counts = 0;

bool powerOn = false;
bool input = false;
//==========START==========
void arduinoStart()
{
  Serial.println("start");
  for(int i = 0; i < 19; i++){
    ledState = !ledState;
    Serial.print(i);
    Serial.print(" ");
    digitalWrite(ledPin, ledState); 
    delay(50);
  }
  Serial.println();
}
void(* resetFunc) (void) = 0;
void powerShift(int _delay = 10)
{
  Serial.print(counts); 
  Serial.print(" - powerShift - "); 
  Serial.println(!powerOn);
  powerOn = !powerOn;
  counts++;
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
  if(!powerOn && counts > 30)
    resetFunc();
    
  delay(_delay);
}
void setup()
{
  Serial.begin(9600); 						// start the serial port
  
  pinMode(ledPin,  OUTPUT);
  pinMode(relePin, OUTPUT);
  pinMode(proximitySwitch, INPUT);

  pinMode(10, OUTPUT); 
  
  arduinoStart();
  digitalWrite(relePin,releState);
}
void loop()
{
  input = !digitalRead(proximitySwitch);
  if(input){
    powerShift();
    int buffState = ledState;
    while(!digitalRead(proximitySwitch)){
      Serial.println("while loop");
      digitalWrite(ledPin, !buffState);
      delay(100);
      digitalWrite(ledPin, buffState); 
      delay(100);
    }
    digitalWrite(ledPin, ledState);
  }
}
