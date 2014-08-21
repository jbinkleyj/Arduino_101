#include <Servo.h>

Servo servo1; Servo servo2; 


void setup() {

  pinMode(1,OUTPUT);
  servo1.attach(14); //analog pin 0
  //servo1.setMaximumPulse(2000);
  //servo1.setMinimumPulse(700);

  servo2.attach(15); //analog pin 1
  
  Serial.begin(115200);
  Serial.print("\r\nArduino_101 SingleServoExampleV2.pde....  Delaying for 2 seconds... ");
}

void loop() {

  static int v = 0;

  if ( Serial.available()) {
    char ch = Serial.read();
    
    switch(ch) {
      case '0'...'9':
        v = v * 10 + ch - '0';
        Serial.print("ch:");Serial.println(v);
        break;
      case 's':
      Serial.print("s:servo1.write(v):");Serial.println(v);
        servo1.write(v);
        v = 0;
        break;
      case 'w':
       Serial.print("w:servo2.write(v):");Serial.println(v);
        servo2.write(v);
        v = 0;
        break;
      case 'd':
        Serial.println("s:servo2.detach:");
        servo2.detach();
        break;
      case 'a':
        Serial.println("s:servo2.attach(15):");
        servo2.attach(15);
        break;
    }
  }

  //Servo::refresh();

} 
