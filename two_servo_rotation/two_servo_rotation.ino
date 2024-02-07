#include <Servo.h> 
Servo servo; 
Servo servo1; 

void setup() {
  // put your setup code here, to run once:
servo.attach(A0); 
  servo1.attach(A1);  
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
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
