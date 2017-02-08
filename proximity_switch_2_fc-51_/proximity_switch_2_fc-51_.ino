const byte     proximitySwitch   = 2;     //пин с прирыванием
const byte     ledPin            = 13;    // номер вывода со светодиодом
byte           ledState          = LOW;
bool           input             = false;
const int      relePin           = 10;      //пин для реле
byte           releState         = LOW;
bool           powerOn           = false;
volatile bool  touch             = false;
//==========START==========
//void(* resetFunc) (void) = 0;
void powerShift(int _delay = 10)
{
  powerOn = !powerOn;
  if(powerOn){
    ledState = LOW;
    releState = HIGH;
  }
  else {
    ledState = HIGH;
    releState = LOW;
  }
  digitalWrite(ledPin,  ledState);
  digitalWrite(relePin, releState);
    
  delay(_delay);
}
void setup()
{
  pinMode(ledPin, OUTPUT);
  // настроить вывод кнопки на вход:
  pinMode(proximitySwitch, INPUT);

  digitalWrite(ledPin, HIGH);
  // прикрепить прерывание к вектору ISR
  attachInterrupt(0, pin_ISR, LOW);
  
  for(int i = 0; i < 19; i++){
    ledState = !ledState;
    digitalWrite(ledPin, ledState); 
    delay(50);
  }
  
  digitalWrite(relePin,releState);
}

void loop()
{
  while (!touch)
    ;

  byte _read = digitalRead(2);
  while (!_read) {
    delay(500);
    _read = digitalRead(2);
  }
//  input = !digitalRead(proximitySwitch);
//  if(input){
//    powerShift();
//    int buffState = ledState;
//    while(!digitalRead(proximitySwitch)){
//      digitalWrite(ledPin, !buffState);
//      delay(100);
//      digitalWrite(ledPin, buffState); 
//      delay(100);
//    }
//    digitalWrite(ledPin, ledState);
//  }

  delay(1000);
  touch = false;
  attachInterrupt(0, pin_ISR, LOW);
}
void pin_ISR()
{
  detachInterrupt(0);
  powerShift(50);
  touch = true;
}
