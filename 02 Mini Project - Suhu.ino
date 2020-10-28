#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

const int ledPinRed =  26;
const int ledPinYellow = 25;
const int ledPinGreen = 33;
const int buttonBlack = 23;
const int pinDHT11 = 27;
DHT dht11(pinDHT11, DHT11);

bool stateON = false;
float temperature = 0.0;


void setup() {
  Serial.begin(115200);
  // set the digital pin as output:
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinYellow, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(buttonBlack, INPUT);
  pinMode(pinDHT11, INPUT);
  dht11.begin();
}

void loop() {
  if (digitalRead(buttonBlack)) {
    if (stateON) {
      stateON = false;
      Serial.println("===============State OFF===============");
    } else {
      stateON = true;
      Serial.println("===============State ON ===============");
    }
    delay(500);
  }
  if (stateON) {
    float t = dht11.readTemperature();
    if (!isnan(t)) {
      temperature = t;
    }
    Serial.print(temperature); Serial.println(" *C, ");

    if (temperature > 34) {
      digitalWrite(ledPinRed, HIGH);
      digitalWrite(ledPinYellow, HIGH);
      digitalWrite(ledPinGreen, HIGH);
    } else if (temperature >=33) {
      digitalWrite(ledPinRed, LOW);
      digitalWrite(ledPinYellow, HIGH);
      digitalWrite(ledPinGreen, HIGH);
    } else if(temperature<33){
      digitalWrite(ledPinRed, LOW);
      digitalWrite(ledPinYellow, LOW);
      digitalWrite(ledPinGreen, HIGH);
    }
  } else {
    digitalWrite(ledPinRed, LOW);
    digitalWrite(ledPinYellow, LOW);
    digitalWrite(ledPinGreen, LOW);
  }
}
