#include <WiFi.h>
#include <ESP32Servo.h>
#include <MQTT.h>

int servoPin = 23;
int ldrPin = 36;
int lightValue = 0;

const char ssid[] = "KuliyahMalam";
const char pass[] = "subscribeduludong";
bool statsOnOff = true;
String stringIni;

Servo myservo;
WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("nodeMCU ESP32", "ff6e7e19", "6d6568ac8b64ae92")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/light");
  client.subscribe("/status");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  if (topic == "/status") {
    if (payload == "1") {
      statsOnOff = true;
    } else {
      statsOnOff = false;
    }
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  client.begin("broker.shiftr.io", net);
  client.onMessage(messageReceived);
  myservo.attach(servoPin);
  myservo.write(100);
  connect();
}

void LightandRotation() {
  lightValue = analogRead(ldrPin);
  stringIni = String(lightValue);
  if (lightValue < 250) {
    myservo.write(0);
  } else if (lightValue >= 250 && lightValue < 3000) {
    myservo.write(90);
  } else {
    myservo.write(160);
  }
}


void loop() {
  client.loop();
  delay(10); 

  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  if (statsOnOff) {
    if (millis() - lastMillis > 1000) {
      lastMillis = millis();
      LightandRotation();
      client.publish("/light", stringIni);
    }
  }
}
