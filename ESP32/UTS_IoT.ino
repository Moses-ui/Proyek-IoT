#include <WiFi.h>
#include "ThingSpeak.h"

const int gpio = 4;
const int led = 2;

const char *writeAPIKey = "JZ51OBBLGM3TCERF";
const char *readAPIKey = "4HUPWPTBRAS5HQ0C";
const char *ssid = "Tubagus ismail lt 14G";
const char *pass = "444444444";
WiFiClient client;
unsigned long channelID = 1;

int state = 0;
int money = (52 + 100) * 1000; // nim: 052, saldo awal: 152.000

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

  while (ThingSpeak.writeField(channelID, 1, money, writeAPIKey) != 200) {
    Serial.println("Failed sending initial money");
  }
}

void loop() {
  state = touchRead(gpio);

  if (state <= 30) { // check if GPIO4 is touched
    if (isMoneySufficient()) {
      while (ThingSpeak.writeField(channelID, 1, money - 20000, writeAPIKey) != 200) {
        Serial.println("Failed sending current money");
      }
      money -= 20000;
      digitalWrite(led, HIGH);
      delay(5000);
    } else {
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
