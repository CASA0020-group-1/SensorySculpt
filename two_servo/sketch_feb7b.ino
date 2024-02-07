#include <Servo.h> // 添加 Servo 库
Servo servo; // 声明 Servo 对象
Servo servo1; // 声明 Servo 对象


void setup() {
  // put your setup code here, to run once:
servo.attach(A0); // 将 Servo 连接到指定引脚
  servo1.attach(A1);  
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
   servo.write(100); // 最大速度正转
    servo1.write(180); // 最大速度正转
  delay(6000); // 根据需要调整延时以控制转动圈数
  
  servo.write(90); // 停止
  servo1.write(90); // 停止
  delay(1000); // 暂停一会儿
  
  servo.write(80); // 最大速度反转
  servo1.write(0); // 最大速度反转
  delay(6000); // 根据需要调整延时以控制转动圈数
  
  servo.write(90); // 停止
   servo1.write(90); // 停止
  delay(1000); // 在下一次循环前暂停一会儿






 
}
