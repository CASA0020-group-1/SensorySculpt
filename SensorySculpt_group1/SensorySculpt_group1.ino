#include <Wire.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h> 
LiquidCrystal_I2C lcd (0x3f, 20, 4);
Servo servo;
 
 
#define SENSOR_PIN A0
#define SERVO_PIN 8
 
void setup ()
{
  pinMode(SENSOR_PIN, INPUT);
  
  servo.attach(SERVO_PIN); // Connect servo to set pin
  servo.write(0); // starting position
  
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.clear();
}
 
void loop ()
{
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
  lcd.print(db,1);
  lcd.print("dB");
  
  if (db < 45)
  {
    lcd.setCursor(0, 1);
    lcd.print("Status: Rest");
    // servo mode: stopped
    servo.writeMicroseconds(1500); 
    delay(30);
  }
  else if (db >= 45 && db < 59)
  {
    lcd.setCursor(0, 1);
    lcd.print("Status: Work");
    // servo mode: circular
    for (int angle = 0; angle <= 180; angle += 1)
    {
      servo.write(angle);
      //delay(15);
    }
    for (int angle = 180; angle >= 0; angle -= 1)
    {
      servo.write(angle);
      //delay(15);
    }

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
  
  delay(1800);
  lcd.clear();
}
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}