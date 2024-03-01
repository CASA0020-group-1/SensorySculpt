#include <Wire.h>
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "arduino_secrets.h"

#define SENSOR_PIN A3

char x;
char currentCase = '1';
String description;
SoftwareSerial mySerial(8, 9);
Adafruit_LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo servo;
Servo servo1;

int pos;
float db;
float temp;
float humidity;
const int speed = 1200;
const int eepromAddress = 0;
unsigned long previousMillis = 0;  // random number time
unsigned long moveMillis = 0;      // servo move time
unsigned long dbCheckMillis = 0;
const long interval = 1000;   // per 1s generate 1 random number
const int moveInterval = 15;  // per 0.015s move servo
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
  Serial.begin(9600);
  //startWifi();
  startWifi();
  //Set pins
  pinMode(SENSOR_PIN, INPUT);
  servo.attach(A0, 500, 2500);  //caibrate servo to PWM signal 500-2500μs
  servo1.attach(A1, 500, 2500);
  //LCD dispkay
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  lcd.clear();

  pos = 1500;
  mySerial.begin(9600);
  Serial.println("HC-05 Bluetooth is ready");
}

void loop() {
  //avoid block
  unsigned long currentMillis = millis();

  //underneath servo move
  //bluetooth read
  if (mySerial.available()) {
    x = mySerial.read();
    currentCase = x;
    Serial.print("Current case updated to: ");
    Serial.println(currentCase);
  }
  if (Serial.available()) {
    x = Serial.read();
    mySerial.print(x);
  }
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


  //get db value every 10s
  
  switch (currentCase) {
      // Room noise
      case '1':
        //lcd print
        if (currentMillis - dbCheckMillis >= dbInterval) {
        dbCheckMillis = currentMillis;
        readapi();
        calculateDb();
        lcd.setCursor(0, 0);
        lcd.print("Loudness: ");
        Serial.print("Room Noise: ");
        Serial.println(db);
        lcd.print(String(db, 1));
        lcd.print("dB");
        }
        break;

      // Temperature
      case '2':
        if (currentMillis - dbCheckMillis >= dbInterval) {
        dbCheckMillis = currentMillis;
        readapi();
        lcd.clear();
        Serial.println(getTemperature());
        lcd.setCursor(0, 0);
        lcd.print("Temperature: ");
        Serial.print("Temperature: ");
        lcd.print(String(temp, 1));
        lcd.print("℃");
        }
        break;

      // Humidity
      case '3':
        if (currentMillis - dbCheckMillis >= dbInterval) {
        dbCheckMillis = currentMillis;
        readapi();
        lcd.clear();
        Serial.println(getHumidity());
        lcd.setCursor(0, 0);
        lcd.print("Humidity: ");
        Serial.print("Humidity: ");
        lcd.print(String(humidity));
        }
        break;
      // Weather description
      case '4':
        //lcd print
        if (currentMillis - dbCheckMillis >= dbInterval) {
        dbCheckMillis = currentMillis;
        readapi();
        lcd.clear();
        
        Serial.print("Weather: ");
        Serial.println(getWeatherDescription());
        lcd.setCursor(0, 1);
        lcd.print(description);
        }
        break;
    }
  

  // Move servo gradually without blocking
}

//function for vlotage calculate
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float calculateDb() {
  unsigned long currentMillis = millis();
  // Calculate noise sensor value to db
  int sensorValue = analogRead(SENSOR_PIN);
  float voltage = sensorValue * (5.0 / 1023.0);                 // map sensor voltage value range from 0~1023 to 0~5
  float mappedVoltage = mapFloat(voltage, 0.0, 5.0, 0.6, 2.6);  // map sensor voltage value range from 0~5 to 0.6~2.6
  db = mapFloat(mappedVoltage, 0.6, 2.6, 30.0, 130.0);          // map sensor voltage value from 0.6~2.6V to 30~130db

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
    servo1.writeMicroseconds(speed);
  } else if (db >= 59) {
    lcd.setCursor(0, 1);
    lcd.print("Status: Noisy");
    //servo mode: random
    // generate random number per second to contrao servo1
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      int randomNumber = random(500, 2501);
      servo1.writeMicroseconds(randomNumber);
    }
  }
  return db;
}

void startWifi() {
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  http = HttpClient(wifiClient, "api.openweathermap.org", 80);
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

    http.beginRequest();
    http.get(finalURL);
    http.endRequest();

    int httpCode = http.responseStatusCode();
    if (httpCode > 0) {
      String JSON_Data = http.responseBody();
      DynamicJsonDocument doc(2048);
      deserializeJson(doc, JSON_Data);
      JsonObject obj = doc.as<JsonObject>();

      description = obj["weather"][0]["description"].as<String>();
      temp = obj["main"]["temp"];
      humidity = obj["main"]["humidity"];
      Serial.println(description);

    } else {
      Serial.print("Error on HTTP request: ");
      Serial.println(httpCode);
    }
  } else {
    Serial.println("WiFi not connected!");
    currentCase = '1';
  }
}

float getTemperature() {
  unsigned long currentMillis = millis();
  if (temp < 12) {
    lcd.setCursor(0, 1);
    lcd.print("Status: Low");
    //SERVO FUNCTION: stop
    servo1.writeMicroseconds(1500);  //servo stop
  } else if (temp >= 12 && temp < 25) {
    lcd.setCursor(0, 1);
    lcd.print("Status: Cozy");
    //SERVO Mode: circle rotation
    servo1.writeMicroseconds(speed);
  } else if (temp >= 25) {
    lcd.setCursor(0, 1);
    lcd.print("Status: High");
    //servo mode: random
    // generate random number per second to contrao servo1
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      int randomNumber = random(500, 2501);
      servo1.writeMicroseconds(randomNumber);
    }
  }
  return temp;
}

float getHumidity() {
  unsigned long currentMillis = millis();
  if (humidity < 60) {
    lcd.setCursor(0, 1);
    lcd.print("Status: Low");
    //SERVO FUNCTION: stop
    servo1.writeMicroseconds(1500);  //servo stop
  } else if (humidity >= 60 && humidity < 90) {
    lcd.setCursor(0, 1);
    lcd.print("Status: Cozy");
    //SERVO Mode: circle rotation
    servo1.writeMicroseconds(speed);
  } else if (humidity >= 90) {
    lcd.setCursor(0, 1);
    lcd.print("Status: High");
    //servo mode: random
    // generate random number per second to contrao servo1
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      int randomNumber = random(500, 2501);
      servo1.writeMicroseconds(randomNumber);
    }
  }
  return humidity;
}

String getWeatherDescription() {
    lcd.setCursor(0, 0);
    servo1.writeMicroseconds(1500);
    lcd.print("Today Weather:");
  return description;
}
