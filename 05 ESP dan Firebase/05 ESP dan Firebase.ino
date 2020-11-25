#include <FirebaseESP32.h>
#include <ESP32Servo.h>
#include <DHT.h>
#include <WiFi.h>

//1. Change the following info
#define FIREBASE_HOST "LINKPROJECT.firebaseio.com/"
#define FIREBASE_AUTH "AUTH_KEY"
#define WIFI_SSID "NAMA_WIFI"
#define WIFI_PASSWORD "PASSWORD"

//Pin yang akan dipakai
int ldrPin = 32;
int dhtPin = 13;
int servoPin = 12;

//Variable yang akan dipakai
float lux = 0;
float tempL = 0;
int angel = 0;
float tempC = 0;
float tempH = 0;
float celcius = 0;
float humidity = 0;
bool sistem = true;
String path = "/node1";

//Object yang akan dipakai
Servo myservo;
DHT dht11(dhtPin, DHT11);
FirebaseData firebaseData;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(dhtPin, INPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  //3. Set your Firebase info
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //4. Enable auto reconnect the WiFi when connection lost
  Firebase.reconnectWiFi(true);

  Firebase.setFloatDigits(2);
  Firebase.setDoubleDigits(2);

  dht11.begin();
  myservo.attach(servoPin);
  myservo.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  Firebase.getString(firebaseData, path + "/sistem");
  if(firebaseData.stringData()=="ON"){
    sistem=true;
  }else{
    sistem=false;
  }
  if (sistem) {
    tempC = dht11.readTemperature();
    if (!isnan (tempC)) {
      celcius = tempC;
      Firebase.setDouble(firebaseData, path + "/suhu", celcius);
    }
    tempH = dht11.readHumidity();
    if (!isnan (tempH)) {
      humidity = tempH;
      Firebase.setDouble(firebaseData, path + "/kelembaban", humidity);
    }
    tempL = analogRead(ldrPin);
    lux = 0.009768 * tempL + 10;
    Firebase.setDouble(firebaseData, path + "/lux", lux);
    if (Firebase.getInt(firebaseData, path + "/servo")) {
      myservo.write(firebaseData.intData());
    }
  }
  delay(100);
}
