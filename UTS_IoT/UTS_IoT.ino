#include <WiFi.h>
#include "ThingSpeak.h"

const int INIT = 1;
const int SUCCESS = 2;
const int FAILED = 3;

const int gpio = 4;
const int led = 2;

const char *writeAPIKey = "548GBNJSVYAIRURX";
const char *readAPIKey = "YJMP9RMTL8LL3KKS";
const char *ssid = "Tubagus ismail lt 14G";
const char *pass = "444444444";
WiFiClient client;
unsigned long channelID = 2;

int state = 0;
int money = (52 + 100) * 1000; // nim: 052, saldo awal: 152.000
int field1Status = 0;
int field2Status = 0;

void connectWifi() {
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println("");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wifi Connected!");
  delay(2000);
}

bool isMoneySufficient() {
  return money >= 20000;
}

void setup() {
  Serial.begin(115200);
  pinMode(gpio, INPUT);
  pinMode(led, OUTPUT);
  connectWifi();
  ThingSpeak.begin(client);

  do {
    field1Status = ThingSpeak.writeField(channelID, 1, money, writeAPIKey);
  } while (field1Status != 200);
  do {
    field2Status = ThingSpeak.writeField(channelID, 2, INIT, writeAPIKey);
  } while (field2Status != 200);
}

void loop() {
  state = touchRead(gpio);
  field1Status = 0;
  field2Status = 0;

  if (state <= 30) { // check if GPIO4 is touched
    if (isMoneySufficient()) {
      money -= 20000;
      do {
        field1Status = ThingSpeak.writeField(channelID, 1, money, writeAPIKey);
      } while (field1Status != 200);
      do {
        field2Status = ThingSpeak.writeField(channelID, 2, SUCCESS, writeAPIKey);
      } while (field2Status != 200);
      digitalWrite(led, HIGH);
      delay(5000);
    } else {
      do {
        // field1Status = ThingSpeak.writeField(channelID, 1, money, writeAPIKey);
        field2Status = ThingSpeak.writeField(channelID, 2, FAILED, writeAPIKey);
      } while (field2Status != 200);
      for (int i = 0; i < 5; i++) {
        digitalWrite(led, HIGH);
        delay(500);
        digitalWrite(led, LOW);
        delay(500);
      } 
    }
  } else {
    digitalWrite(led, LOW);
  }
}
