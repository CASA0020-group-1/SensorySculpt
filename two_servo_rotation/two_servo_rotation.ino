#include <Wire.h>
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>
#include <EEPROM.h>
#include "arduino_secrets.h"

#define SENSOR_PIN A3

Adafruit_LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo servo;
Servo servo1;

int pos;
int maxPulse = 2500;
int minPulse = 500;
int delayTime = 15;
float db;
const int eepromAddress = 0;  
unsigned long previousMillis = 0;  // random number time
unsigned long moveMillis = 0;      // servo move time
unsigned long dbCheckMillis = 0; 
const long interval = 1000;        // per 1s generate 1 random number
const int moveInterval = 15;       // per 0.015s move servo
const long dbInterval = 10000;  
bool increasing = true;

//set Wifi
const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;
const char* ApiKey = SECRET_API;

String URL = "http://api.openweathermap.org/data/2.5/weather?";

// Set location
String lat = "51.6116402309989";
String lon = "-0.12889632674983237";

WiFiClient wifiClient;
HttpClient http(wifiClient, URL, 80);
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);

void setup() {
  Serial.begin(115200);
  //startWifi();

  //Set pins
  pinMode(SENSOR_PIN, INPUT);


  servo.attach(A0, 500, 2500);  //caibrate servo to PWM signal 500-2500μs
  servo1.attach(A1, 500, 2500);
    
  //LCD dispkay
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  lcd.clear();
}

void loop() {
  //avoid block
  unsigned long currentMillis = millis();

  //get db value every 10s 
  if (currentMillis - dbCheckMillis >= dbInterval) {
    dbCheckMillis = currentMillis;
    float db = calculateDb(); 
    //lcd print
    lcd.setCursor(0, 0);
    lcd.print("Loudness: ");
    Serial.println("db:");
    Serial.println(db);
    lcd.print(db, 1);
    lcd.print("dB");
  }

  //upper servo rotation function
  if (db < 40) {
    lcd.setCursor(0, 1);
    lcd.print("Status: Rest");
    //SERVO FUNCTION: stop
    servo1.writeMicroseconds(1500);  //servo stop
  } else if (db >= 40 && db < 59) {
    lcd.setCursor(0, 1);
    lcd.print("Status: Work");
    //SERVO Mode: circle rotation
    int speed = map(db,40,59,1300,1000);
    servo1.writeMicroseconds(speed);
  } else if (db >= 59) {
    lcd.setCursor(0, 1);
    lcd.print("Status: Noisy");
    //servo mode: random
    // generate random number per second to contrao servo1
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      int randomNumber = random(500, 2501);
      Serial.println(randomNumber);
      servo1.writeMicroseconds(randomNumber);
    }
  }

   // Move servo gradually without blocking
    if (currentMillis - moveMillis >= moveInterval) {
      moveMillis = currentMillis;
      servo.writeMicroseconds(pos);
      if (increasing) {
        pos += 2;
        if (pos >= 2500) increasing = false;
      } else {
        pos -= 2;
        if (pos <= 500) increasing = true;
      }
  }
}

//function for vlotage calculate
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float calculateDb() {
 // Calculate noise sensor value to db
  int sensorValue = analogRead(SENSOR_PIN);
  float voltage = sensorValue * (5.0 / 1023.0);                 // map sensor voltage value range from 0~1023 to 0~5
  float mappedVoltage = mapFloat(voltage, 0.0, 5.0, 0.6, 2.6);  // map sensor voltage value range from 0~5 to 0.6~2.6
  db = mapFloat(mappedVoltage, 0.6, 2.6, 30.0, 130.0);    // map sensor voltage value from 0.6~2.6V to 30~130db
  return db;
}

void startWifi() {
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // check to see if connected and wait until you are
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void readapi() {
    if (WiFi.status() == WL_CONNECTED) {
      String lat = "51.6116402309989";
      String lon = "-0.12889632674983237";

      String finalURL = URL + "lat=" + lat + "&lon=" + lon + "&units=metric&appid=" + ApiKey;
      Serial.println(finalURL);
      http.beginRequest();
      http.get(finalURL);
      http.endRequest();

      int httpCode = http.responseStatusCode();
      if (httpCode > 0) {
        String JSON_Data = http.responseBody();

        Serial.println(JSON_Data);

        DynamicJsonDocument doc(2048);
        deserializeJson(doc, JSON_Data);
        JsonObject obj = doc.as<JsonObject>();

        const char* description = obj["weather"][0]["description"];
        const float temp = obj["main"]["temp"];
        const float humidity = obj["main"]["humidity"];
        Serial.println(description);
        Serial.println(temp);
        Serial.println(humidity);
      
      }else {
        Serial.print("Error on HTTP request: ");
        Serial.println(httpCode);
      }
      } else {
        Serial.println("WiFi not connected!");
      }
}
    
  
  
