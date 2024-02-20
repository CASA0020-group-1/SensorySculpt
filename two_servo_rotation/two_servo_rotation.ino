#include <Wire.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h> 

LiquidCrystal_I2C lcd (0x3f, 20, 4);
Servo servo; 
Servo servo1; 

#define SENSOR_PIN A3

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);


void setup() {
  // put your setup code here, to run once:
  pinMode(SENSOR_PIN, INPUT);

  servo.attach(A0); 
  servo1.attach(A1);  
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {

    // read sensor voltage
  int sensorValue = analogRead(SENSOR_PIN);
  // map sensor voltage value range from 0~1023 to 0~5
  float voltage = sensorValue * (5.0 / 1023.0); 

  // map sensor voltage value range from 0~5 to 0.6~2.6
  float mappedVoltage = mapFloat(voltage, 0.0, 5.0, 0.6, 2.6);

  // map sensor voltage value from 0.6~2.6V to 30~130db
  float db = mapFloat(mappedVoltage, 0.6, 2.6, 30.0, 130.0);


  lcd.setCursor(0, 0);
  lcd.print("Loudness: ");
 
  
  Serial.println(sensorValue);
  Serial.println("db");
  Serial.println(db);
  lcd.print(db,1);
  lcd.print("dB");

  if (db < 45)
  {
    lcd.setCursor(0, 1);
    lcd.print("Status: Rest");
    // servo mode: stopped
    servo.write(80); 
    delay(30);
  }
  else if (db >= 45 && db < 59)
  {
    lcd.setCursor(0, 1);
    lcd.print("Status: Work");
    servo.write(100); 
    servo1.write(180); 
    delay(6000); 
    servo.write(90); 
    servo1.write(90); // 
    delay(1000); // 
    
    servo.write(80); 
    servo1.write(0); // 
    delay(6000); 
    
    servo.write(90); 
    servo1.write(90); 
    delay(1000); 
    }
   

  else if (db >= 59)
  {
    lcd.setCursor(0, 1);
    lcd.print("Status: Noisy");
    // servo mode: random
    int randomAngle = random(0, 180);
    servo.write(randomAngle);
    delay(30); 
  }

  // put your main code here, to run repeatedly:
  
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
