
const int ledPinRed =  26;
const int ledPinYellow = 25;
const int ledPinGreen = 33;

unsigned long previousMillis = 0;     
int counter = 0;


// constants won't change:
const long intervalRed = 3000;          
const long intervalYellow = 1000;
const long intervalGreen = 2000;

void setup() {
  // set the digital pin as output:
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinYellow, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (counter == 0) {
    digitalWrite(ledPinRed, HIGH);
    digitalWrite(ledPinYellow, LOW);
    digitalWrite(ledPinGreen, LOW);
    counter++;
    previousMillis += intervalRed;
  }else{
      if(counter == 1 && previousMillis - currentMillis == 0){
          digitalWrite(ledPinRed, LOW);
          digitalWrite(ledPinYellow, HIGH);
          counter++;
          previousMillis += intervalYellow;
      }else if(counter == 2 && previousMillis - currentMillis == 0){
          digitalWrite(ledPinYellow, LOW);
          digitalWrite(ledPinGreen, HIGH);
          counter++;
          previousMillis += intervalGreen;
      }else if(counter == 3 && previousMillis - currentMillis == 0){ 
          digitalWrite(ledPinRed, HIGH);
          digitalWrite(ledPinGreen, LOW);
          counter = 1;
          previousMillis += intervalRed;
      }
  }
}
